#include "graphics.h"
#include "graphics_macros.h"
#include "errors.h"

#include <lcom/lcf.h>

#include <stdio.h>

static void *video_mem; /** @brief Frame-buffer VM address */
static vbe_mode_info_t vbe_mem_info;
static mmap_t mem_map;

int (get_permission)(unsigned int base_addr, unsigned int size) {
    return 1;
}

//int (get_permissions_first_mbyte)(void) {
//    return get_permission(MBYTE_BASE, MBYTE_SIZE);
//}

int (vbe_get_mode_information)(uint16_t mode) {
    return 1;
}

int (vbe_get_controller_information)(vg_vbe_contr_info_t *info_p) {
    return 1;
}

phys_bytes get_phys_addr(void) {
    return 1
}

unsigned int get_vram_size(void) {
    return 1;
}

uint16_t get_XRes(void) {
    return 1;
}

uint16_t get_YRes(void) {
    return 1;
}

uint16_t get_bits_pixel(void) {
    return 1;
}

uint16_t get_bytes_pixel(void) {
    return 1;
}

uint16_t get_RedMaskSize  (void){ return 1; }
uint16_t get_GreenMaskSize(void){ return 1; }
uint16_t get_BlueMaskSize (void){ return 1; }

int (map_vram)(void) {
    return 1;
}

int (free_memory_map)(void) {
    return 1;
}

int (set_graphics_mode)(uint16_t mode) {
    return 1;
}


int (set_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    return 1;
}

int (draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    return 1;
}
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    return 1;
}

int (draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color)	{
    return 1;
}
int (vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color){
    return 1;
}

int paint_screen(uint32_t color){
    return 1;
}

int clear_screen(){
    return 1;
}
