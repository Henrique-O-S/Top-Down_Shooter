#include <lcom/lcf.h>

#include "video_gr.h"

reg86_t reg86;

static uint16_t hres;
static uint16_t vres;
static uint8_t color_depth;
static uint8_t memory_mode;
static uint8_t red_pos;
static uint8_t red_size;
static uint8_t green_pos;
static uint8_t green_size;
static uint8_t blue_pos;
static uint8_t blue_size;
static void* video_memory;
    
void* vg_init(uint16_t mode){
    vbe_mode_info_t mode_info;

    if(vbe_get_mode_info(mode, &mode_info) != 0){
        printf("vg_init(): vbe_get_mode_info() failed \n");
        return 1;
    }

    
    reg86.intno = 0x10;
    reg86.ah = 0x4F;
    reg86.al = 0x02;
    reg86.bx = 1 << 14 | mode;
    if( sys_int86(&reg86) != 0 ) {
        printf("vg_init(): sys_int86() failed \n");
        return 1;
    }
    return 0;
}

