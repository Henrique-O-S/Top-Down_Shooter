#include "../include/graphics.h"
#include <stdio.h>
#include "../include/graphics_macros.h"
#include <math.h>
#include "sprite.h"
#include "graphics.h"
#include "utils.h"
#include "mouse.h"
#include "aux_functions.h"

static uint8_t *video_mem; /** @brief Frame-buffer VM address */
static uint8_t *double_buffer; /** @brief Frame-buffer VM address */
static vbe_mode_info_t vbe_mem_info;
static mmap_t mem_map;

uint16_t get_XRes(void) {
    return vbe_mem_info.XResolution;
}

uint16_t get_YRes(void) {
    return vbe_mem_info.YResolution;
}

uint16_t get_bits_pixel(void) {
    return vbe_mem_info.BitsPerPixel;
}

uint16_t get_bytes_pixel(void) {
    return (vbe_mem_info.BitsPerPixel + 7) >> 3;
}

phys_bytes get_phys_addr(void) {
    return vbe_mem_info.PhysBasePtr;
}

uint16_t get_RedMaskSize (void) { 
    return vbe_mem_info.RedMaskSize; 
}

uint16_t get_GreenMaskSize (void) { 
    return vbe_mem_info.GreenMaskSize; 
}

uint16_t get_BlueMaskSize (void) { 
    return vbe_mem_info.BlueMaskSize ; 
}

int (vbe_get_mode_information)(uint16_t mode) {
    memset(&vbe_mem_info, 0, sizeof(vbe_mode_info_t)); // reset values

    reg86_t r;

    memset(&r, 0, sizeof(reg86_t)); // reset struct

    vbe_mode_info_t *virtual_addr = lm_alloc(sizeof(vbe_mode_info_t),&mem_map);

    r.intno = VC_BIOS_SERV;
    r.ah = VBE_CALL; 
    r.al = VBE_MD_INFO;
    r.cx = mode;
    r.es = PB2BASE(mem_map.phys);
    r.di = PB2OFF(mem_map.phys);
    // BIOS CALL
    if (sys_int86(&r)) {
        printf("%s: sys_int86 failed\n", __func__);
        if (free_memory_map()) {
            printf("%s: lm_free failed\n", __func__);
        }
        return 1;
    }

    memcpy((void*)&vbe_mem_info, (void*)virtual_addr, mem_map.size);
    return 0;
}

int (set_vbe_mode)(uint16_t mode) {
    reg86_t r;

    memset(&r, 0, sizeof(reg86_t));

    r.ah = VBE_CALL; 
    r.al = FUNC_02;
    r.bx = LINEAR_FRAME_BUFFER_MD | mode;
    r.intno = VC_BIOS_SERV;
    if(sys_int86(&r) != OK) {
        printf("set_vbe_mode: sys_int86() failed\n");
        return 1;
    }
    return 0;
}

int (get_permission)(unsigned int base_addr, unsigned int size) {
    struct minix_mem_range mr;
    mr.mr_base = base_addr;
    mr.mr_limit = base_addr + size;
    return sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr);
}

int (map_vram)(void) {
    int r;
    unsigned int vram_base = get_phys_addr();
    unsigned int vram_size = get_vram_size();
    if ((r = get_permission(vram_base, vram_size))) {
        if (free_memory_map()) {
            printf("%s: lm_free failed\n", __func__);
        }
        panic("%s: sys_privctl (ADD MEM) failed: %d\n", __func__, r);
    }

    video_mem = vm_map_phys(SELF, (void *)vram_base, vram_size);

    if (video_mem == MAP_FAILED) {
        if (free_memory_map()) {
            printf("%s: lm_free failed\n", __func__);
        }
        panic("%s: couldn't map video memory.", __func__);
    }

    double_buffer = malloc(vram_size);
    return 0;
}

int (set_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x >= vbe_mem_info.XResolution || y >= vbe_mem_info.YResolution) {
        printf("%s: invalid pixel.\n", __func__);
        return 1;
    }
    unsigned int pos = (x + y * vbe_mem_info.XResolution) * get_bytes_pixel();
    memcpy((void*)((unsigned int)double_buffer + pos), &color, get_bytes_pixel());
    return 0;
}


int (draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    int r;
    for (uint16_t i = 0; i < len; i++)
        if ((r = set_pixel(x + i, y, color))) return 1;
    return 0;
}

int (draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color)	{
    int r;
    for (uint16_t i = 0; i < height; i++)
        if ((r = draw_hline(x, y + i, width, color))) return 1;
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color)	{
    return draw_rectangle(x, y, width, height, color);
}

unsigned int get_vram_size(void) {
    return vbe_mem_info.XResolution * vbe_mem_info.YResolution * ((vbe_mem_info.BitsPerPixel + 7) >> 3);
}

int(free_memory_map)(void) {
    return !lm_free(&mem_map);
}

void (draw_double_buffer)(void) {
    memcpy(video_mem, double_buffer, get_YRes()*get_XRes()*get_bytes_pixel());
}

int paint_screen(uint32_t color){
    return draw_rectangle(0,0,get_XRes(),get_YRes(),color);
}

int clear_screen(){
    memset(double_buffer, 0, get_vram_size());
    return 0;
}


/******* SPRITE *******/

basic_sprite_t* (basic_sprite_ctor)(const char *const *xpm, int16_t x_offset, int16_t y_offset){
    basic_sprite_t *ret = malloc(sizeof(basic_sprite_t));
    if(ret == NULL) return NULL;
    enum xpm_image_type type = XPM_8_8_8_8;
    xpm_image_t img;
    ret->map = xpm_load((xpm_map_t)xpm, type, &img);
    if(ret->map == NULL){
        basic_sprite_dtor(ret);
        return NULL;
    }
    ret->w = img.width;
    ret->h = img.height;
    ret->x_offset = x_offset;
    ret->y_offset = y_offset;
    return ret;
}

void (basic_sprite_dtor)(basic_sprite_t *p){
    if(p == NULL) return;
    free(p->map);
    free(p);
}

const uint8_t* (basic_sprite_get_map)(const basic_sprite_t *p){ return p->map; }

uint16_t       (basic_sprite_get_w)  (const basic_sprite_t *p){ return p->w  ; }

uint16_t       (basic_sprite_get_h)  (const basic_sprite_t *p){ return p->h  ; }

int16_t        (basic_sprite_get_x_offset) (const basic_sprite_t *p){ return p->x_offset ; }

int16_t        (basic_sprite_get_y_offset) (const basic_sprite_t *p){ return p->y_offset ; }

sprite_t* (sprite_ctor)(basic_sprite_t **bsp, uint8_t animation){
    sprite_t *ret = malloc(sizeof(sprite_t));
    if(ret == NULL) return NULL;
    ret->animation = animation;
    ret->current_animation = 0;
    ret->current_wait = 0;
    ret->wait = 0;
    ret->bsp =(basic_sprite_t**)malloc(sizeof(basic_sprite_t*)* animation);
    for(int i = 0; i < animation; i++) {
        ret->bsp[i] = bsp[i];
    }
    ret->x = 0;
    ret->y = 0;
    ret->x_offset = (int16_t)(ret->bsp[0]->x_offset);
    ret->y_offset = (int16_t)(ret->bsp[0]->y_offset);

    sprite_set_angle(ret, 0.0);

    return ret;
}

void (sprite_dtor)(sprite_t *p){
    if(p == NULL) return;
    free(p);
}

void (sprite_set_pos) (sprite_t *p, int16_t x, int16_t y){ p->x = x; p->y = y; }

void (sprite_set_angle) (sprite_t *p, double angle){ p->angle = angle; p->c = cos(p->angle); p->s = sin(p->angle); }

double   (sprite_get_angle) (const sprite_t *p){ return p->angle; }

uint16_t (sprite_get_w)(const sprite_t *p){ 
    return basic_sprite_get_w(p->bsp[0]); 
}

uint16_t (sprite_get_h)(const sprite_t *p){ 
    return basic_sprite_get_h(p->bsp[0]); 
}

uint16_t (sprite_get_X)(const sprite_t *p) {
    return p->x;
}

uint16_t (sprite_get_Y)(const sprite_t *p) {
    return p->y;
}

double (sprite_angle_of_two)(const sprite_t *p, const sprite_t *p1) {
    return atan2(sprite_get_Y(p1) - sprite_get_Y(p), sprite_get_X(p) - sprite_get_X(p1));
}

// Change to sprite_set_rotation
static void (sprite_src2sbuf)(const sprite_t *p, int16_t x, int16_t y, int16_t *u, int16_t *v){
    if(p->angle == 0.0){
        *u = x - p->x + p->x_offset;
        *v = y - p->y + p->y_offset;
    }else{
        double dx = x - p->x;
        double dy = y - p->y;
        int16_t du = (int16_t)(dx*p->c - dy*p->s);
        int16_t dv = (int16_t)(dx*p->s + dy*p->c);
        *u = du + p->x_offset;
        *v = dv + p->y_offset;
    }
}

static void (sprite_set_corner_for_rotation)(const sprite_t *p, int16_t u, int16_t v, int16_t *x, int16_t *y){
    int16_t du = u - p->x_offset; // set for x_offset
    int16_t dv = v - p->y_offset; // set for y_offset
    double dx =  du*p->c + dv*p->s;
    double dy = -du*p->s + dv*p->c;
    *x = (int16_t)(dx + p->x);
    *y = (int16_t)(dy + p->y);
}

void (sprite_draw)(const sprite_t *p){
    int animation = p->current_animation;
    const uint16_t sw = (uint16_t)(basic_sprite_get_w(p->bsp[0]));
    const uint16_t sh = (uint16_t)(basic_sprite_get_h(p->bsp[0]));
    int16_t xmin, xmax, ymin, ymax;
    int16_t x, y;
    sprite_set_corner_for_rotation(p, 0, 0, &x, &y);                     // TOP LEFT
    xmin = x; xmax = x; ymin = y; ymax = y;
    sprite_set_corner_for_rotation(p, (int16_t)sw, 0, &x, &y);           // TOP RIGHT
    xmin = min(x, xmin); xmax = max(x, xmax); ymin = min(y, ymin); ymax = max(y, ymax);
    sprite_set_corner_for_rotation(p, 0, (int16_t)sh, &x, &y);           // BOTTOM LEFT
    xmin = min(x, xmin); xmax = max(x, xmax); ymin = min(y, ymin); ymax = max(y, ymax);
    sprite_set_corner_for_rotation(p, (int16_t)sw, (int16_t)sh, &x, &y); // BOTTOM RIGHT
    xmin = min(x, xmin); xmax = max(x, xmax); ymin = min(y, ymin); ymax = max(y, ymax);
    xmin = max(xmin, 0); xmax = min(xmax, (int16_t)get_XRes());
    ymin = max(ymin, 0); ymax = min(ymax, (int16_t)get_YRes());
    
    const uint16_t bytes_pixel = 3;
    for(int16_t u, v, y = ymin; y < ymax; ++y){
        uint8_t *place = double_buffer + (xmin + y*get_XRes())*bytes_pixel;
        for(int16_t x = xmin; x < xmax; ++x, place += bytes_pixel){
            sprite_src2sbuf(p, x, y, &u, &v);
            if(0 <= u && u < sw && 0 <= v && v < sh){
                const uint8_t *color = basic_sprite_get_map(p->bsp[animation])+(v*sw+u)*4;
                if(*(color+3) < ALPHA_THRESHOLD){ //alpha
                    memcpy(place, color, bytes_pixel);
                }
            }
        }
    }
}

void (sprite_update_animation) (sprite_t *p, int reset) {
    if(reset) {
        p->current_wait = 0;
        p->current_animation = 0;
        return;
    }
    p->current_wait++;
    if(p->current_wait >= p->wait) {
        p->current_wait = 0;
        p->current_animation++;
        if(p->current_animation >= p->animation) p->current_animation = 0;
    }
}

void (sprite_choose_animation) (sprite_t *p, int animation) {
    if(animation < 0 || animation > p->animation) p->current_animation = 0;
    else p->current_animation = animation;
}
