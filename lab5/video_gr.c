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
    
void* (vg_init)(uint16_t mode){
    vbe_mode_info_t mode_info;

    if(vbe_get_mode_info(mode, &mode_info) != 0){
        printf("vg_init(): vbe_get_mode_info() failed \n");
        return NULL;
    }

    if(mem_map(mode_info)) return NULL;

    reg86.intno = 0x10;
    reg86.ah = 0x4F;
    reg86.al = 0x02;
    reg86.bx = 1 << 14 | mode;
    if( sys_int86(&reg86) != 0 ) {
        printf("vg_init(): sys_int86() failed \n");
        return NULL;
    }
    return video_memory;
}

 int (mem_map)(vbe_mode_info_t mode_info) {
    
    hres = mode_info.XResolution;
    vres = mode_info.YResolution;
    color_depth = mode_info.BitsPerPixel;
    memory_mode = mode_info.MemoryModel;

    if(memory_mode == mode_info.DirectColorModeInfo){
        red_pos = mode_info.RedFieldPosition;
        red_size = mode_info.RedMaskSize;
        green_pos = mode_info.GreenFieldPosition;
        green_size = mode_info.GreenMaskSize;
        blue_pos = mode_info.BlueFieldPosition;
        blue_size = mode_info.BlueMaskSize;
    }

    struct minix_mem_range mr;
    int vram_size = hres * vres * color_depth;
    mr.mr_base = (phys_bytes) mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + vram_size;

    int r;
    if((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK){
        printf("sys_privctl (ADD_MEM) failed: %d\n", r);
        return 1;
    }
    
    video_memory = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);


    if(video_memory == MAP_FAILED){
        printf("couldn't map video memory\n");
        return 1;   
    }

    return 0;
 }


int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t  width, uint16_t	height, uint32_t color){
    for(int yn = y; yn - y < height; yn++){
        if(vg_draw_hline(x, yn, width, color)) {
            printf("failed to draw hline");
            return 1;
        }
    }
    return 0;
}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    for(int xn = x; xn - x < len; xn++){
        if(vg_draw_pixel(xn, y, color)){
            printf("failed to draw pixel");
            return 1;
        };
    }	
    return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){

    if(color_depth <= 8){
        uint8_t* pixel_address = (uint8_t*)video_memory + (x + y*hres); 
        *pixel_address = color;
        return 0;
    }
    else if(color_depth <= 16) {
        uint16_t* pixel_address = (uint16_t*)video_memory + (x + y*hres)*2;
        *pixel_address = color;
        return 0;
    }
    else if(color_depth == 24) {
        uint8_t* pixel_addressR = (uint8_t*)video_memory + (x + y*hres)*3;
        uint8_t* pixel_addressG = (uint8_t*)video_memory + (x + y*hres)*3 + 1;
        uint8_t* pixel_addressB = (uint8_t*)video_memory + (x + y*hres)*3 + 2;
        *pixel_addressR = color;
        *pixel_addressG = color >> 8;
        *pixel_addressB = color >> 16;
        return 0;
    }
    else if(color_depth <= 32){
        uint32_t* pixel_address = (uint32_t*)video_memory + (x + y*hres)*4;
        *pixel_address = color;
         return 0;
    }   

    return 1;    
}
