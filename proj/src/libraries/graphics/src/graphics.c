#include "../include/graphics.h"
#include <stdio.h>
#include "../include/graphics_macros.h"
#include <math.h>
#include "sprite.h"
#include "graphics.h"
#include "utils.h"

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

void (swapBuffer()) {
    memcpy(double_buffer, video_mem, get_YRes()*get_XRes()*get_bytes_pixel());
}

int (pixmap_drawer)(uint16_t x, uint16_t y, enum pixmap pixmap){
    unsigned int height = 0, width = 0;

    if (pixmap == PLAY || pixmap == EXIT) height = 37;
    if (pixmap == PLAY) width = 271;
    if (pixmap == EXIT) width = 207;
    
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int j = 0; j < width; j++){
            if (pixmap == PLAY){
                if (play[i][j] == '0') set_pixel(x + j, y + i, PLAY_COLOR);
                else if(play[i][j] == '1') set_pixel(x + j, y + i, MENU_BACKGROUND_COLOR);
            }

            if (pixmap == EXIT){
                if (exitPix[i][j] == '0') set_pixel(x + j, y + i,EXIT_COLOR);
                else if(exitPix[i][j] == '1') set_pixel(x + j, y + i, MENU_BACKGROUND_COLOR);
            }
        }
    }

    return 0;
}


/******* SPRITE *******/


struct basic_sprite{
    uint8_t *map;
    uint16_t w, h;
    int16_t u0, v0;
};
struct sprite{
    const basic_sprite_t *bsp;
    int16_t x, y; //position in screen
    int16_t su0, sv0;
    double theta, s, c;
    double scale;
    uint8_t *sbuf;
};

basic_sprite_t* (basic_sprite_ctor)(const char *const *xpm, int16_t u0, int16_t v0){
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
    ret->u0 = u0;
    ret->v0 = v0;
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

int16_t        (basic_sprite_get_u0) (const basic_sprite_t *p){ return p->u0 ; }

int16_t        (basic_sprite_get_v0) (const basic_sprite_t *p){ return p->v0 ; }

sprite_t* (sprite_ctor)(const basic_sprite_t *bsp){
    sprite_t *ret = malloc(sizeof(sprite_t));
    if(ret == NULL) return NULL;
    ret->bsp = bsp;
    ret->sbuf = NULL;
    ret->x = 0;
    ret->y = 0;
    sprite_set_angle(ret, 0.0);
    sprite_set_scale(ret, 1.0);
    return ret;
}

void (sprite_dtor)(sprite_t *p){
    if(p == NULL) return;
    free(p->sbuf);
    free(p);
}

void (sprite_set_pos)   (sprite_t *p, int16_t x , int16_t y ){ p->x = x; p->y = y; }

void (sprite_set_angle) (sprite_t *p, double angle          ){ p->theta = angle; p->c = fm_cos(p->theta); p->s = fm_sin(p->theta); }

void (sprite_set_scale) (sprite_t *p, double scale          ){
    //if(eq_d(p->scale, scale)) return;
    p->scale = scale;

    p->su0 = (int16_t)(p->bsp->u0*p->scale);
    p->sv0 = (int16_t)(p->bsp->u0*p->scale);

    const uint16_t W = basic_sprite_get_w(p->bsp),
                   H = basic_sprite_get_h(p->bsp);
    uint16_t sW = (uint16_t)(W*scale), sH = (uint16_t)(H*scale);
    p->sbuf = realloc(p->sbuf, sW*sH*4);
    const uint8_t *map = basic_sprite_get_map(p->bsp);
    for(uint16_t sx = 0; sx < sW; ++sx){
        for(uint16_t sy = 0; sy < sH; ++sy){
            uint16_t x = (uint16_t)(sx/scale), y = (uint16_t)(sy/scale);
            if(x > W || y > H) continue;
            memcpy(p->sbuf+4*(sx+sy*sW), map+4*(x+y*W), 4);
        }
    }
}

double   (sprite_get_angle)(const sprite_t *p){ return p->theta; }

uint16_t (sprite_get_w)(const sprite_t *p){ 
    return basic_sprite_get_w(p->bsp); 
}

uint16_t (sprite_get_h)(const sprite_t *p){ 
    return basic_sprite_get_h(p->bsp); 
}

uint16_t (sprite_get_X)(const sprite_t *p) {
    return p->x;
}

uint16_t (sprite_get_Y)(const sprite_t *p) {
    return p->y;
}

static void (sprite_src2sbuf)(const sprite_t *p, int16_t x, int16_t y, int16_t *u, int16_t *v){
    if(p->theta == 0.0){
        *u = x - p->x + p->su0;
        *v = y - p->y + p->sv0;
    }else{
        double dx = x - p->x;
        double dy = y - p->y;
        int16_t du = (int16_t)(dx*p->c - dy*p->s - 0.5f);
        int16_t dv = (int16_t)(dx*p->s + dy*p->c - 0.5f);
        *u = du + p->su0;
        *v = dv + p->sv0;
    }
}

static void (sprite_sbuf2src)(const sprite_t *p, int16_t u, int16_t v, int16_t *x, int16_t *y){
    int16_t du = u - p->su0;
    int16_t dv = v - p->sv0;
    double dx =  du*p->c + dv*p->s;
    double dy = -du*p->s + dv*p->c;
    *x = (int16_t)(dx + 0.5 + p->x);
    *y = (int16_t)(dy + 0.5 + p->y);
}

void (sprite_draw)(const sprite_t *p){
    const uint16_t sw = (uint16_t)(p->scale*basic_sprite_get_w(p->bsp));
    const uint16_t sh = (uint16_t)(p->scale*basic_sprite_get_h(p->bsp));
    int16_t xmin, xmax, ymin, ymax; {
        int16_t x, y;
        sprite_sbuf2src(p, 0, 0, &x, &y);
        xmin = x; xmax = x; ymin = y; ymax = y;
        sprite_sbuf2src(p, (int16_t)sw, 0          , &x, &y);
        xmin = min(x, xmin); xmax = max(x, xmax); ymin = min(y, ymin); ymax = max(y, ymax);
        sprite_sbuf2src(p, 0, (int16_t)sh, &x, &y);
        xmin = min(x, xmin); xmax = max(x, xmax); ymin = min(y, ymin); ymax = max(y, ymax);
        sprite_sbuf2src(p, (int16_t)sw, (int16_t)sh, &x, &y);
        xmin = min(x, xmin); xmax = max(x, xmax); ymin = min(y, ymin); ymax = max(y, ymax);
        xmin = max(xmin-2, 0); xmax = min(xmax+2, (int16_t)get_XRes());
        ymin = max(ymin-2, 0); ymax = min(ymax+2, (int16_t)get_YRes());
    }
    const uint16_t bytes_pixel = 3;
    for(int16_t u, v, y = ymin; y < ymax; ++y){
        uint8_t *place = double_buffer + (xmin + y*get_XRes())*bytes_pixel;
        for(int16_t x = xmin; x < xmax; ++x, place += bytes_pixel){
            sprite_src2sbuf(p, x, y, &u, &v);
            if(0 <= u && u < sw && 0 <= v && v < sh){
                const uint8_t *c_p = p->sbuf+(v*sw+u)*4;
                if(*(c_p+3) < ALPHA_THRESHOLD){ //alpha
                    memcpy(place, c_p, bytes_pixel);
                }
            }
        }
    }
}
