#include "graphics.h"
#include <stdio.h>
#include "graphics_macros.h"


static void *video_mem; /** @brief Frame-buffer VM address */
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

    return 0;
}

int (set_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x >= vbe_mem_info.XResolution || y >= vbe_mem_info.YResolution) {
        printf("%s: invalid pixel.\n", __func__);
        return 1;
    }
    unsigned int pos = (x + y * vbe_mem_info.XResolution) * get_bytes_pixel();
    memcpy((void*)((unsigned int)video_mem + pos), &color, get_bytes_pixel());
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

int paint_screen(uint32_t color){
    return draw_rectangle(0,0,get_XRes(),get_YRes(),color);
}

int clear_screen(){
    return paint_screen(BLACK);
}
