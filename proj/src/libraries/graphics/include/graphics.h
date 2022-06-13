#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

/**
 * @defgroup graphics graphics
 * @ingroup libraries
 *
 * @{
 */

#include <lcom/lcf.h>
#include <stdint.h>
#include "graphics_macros.h"

#define GET_RED(n)          (0xFF & ((n) >> 16))
#define GET_GRE(n)          (0xFF & ((n) >>  8))
#define GET_BLU(n)          (0xFF & (n      ))
#define SET_RED(n)          (((n)&0xFF) << 16)
#define SET_GRE(n)          (((n)&0xFF) <<  8)
#define SET_BLU(n)          (((n)&0xFF)      )
#define SET_COLOR(r,g,b)    (SET_RED(r) | SET_GRE(g) | SET_BLU(b))
#define FAR2PHYS(n)         ((((n)>>12) & 0xFFFFFFF0) + ((n) & 0x0000FFFF))

/**
 * @brief sets video graphics mode
 * @param mode mode to choose
 * @return 0 if sucessful, 1 otherwise
 */
int (set_vbe_mode)(uint16_t mode);

/**
 * @brief sets pixel into the buffer
 * @param x horizontal position
 * @param y vertical position
 * @param color color to be put into the buffer
 * @return 0 if sucessful, 1 otherwise
 */
int (set_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief draws horizontal line into the buffer
 * @param x horizontal position
 * @param y vertical position
 * @param len lenght of the horizontal line
 * @param color color to be put into the buffer
 * @return 0 if sucessful, 1 otherwise
 */
int (draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief draws rectangle into the buffer
 * @param x horizontal position
 * @param y vertical position
 * @param width width of the rectangle
 * @param height height of the rectangle
 * @param color color to be put into the buffer
 * @return 0 if sucessful, 1 otherwise
 */
int (draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief aux function to draw rectangle into the buffer
 * @param x horizontal position
 * @param y vertical position
 * @param width width of the rectangle
 * @param height height of the rectangle
 * @param color color to be put into the buffer
 * @return 0 if sucessful, 1 otherwise
 */
int (vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief gets permission for the given address
 * @param base_addr base address
 * @param size lenght of the address
 * @return 0 if sucessful, 1 otherwise
 */
int (get_permission)(unsigned int base_addr, unsigned int size);

/**
 * @brief gets information for given video graphics mode
 * @param mode mode to choose
 * @return 0 if available, 1 otherwise
 */
int (vbe_get_mode_information)(uint16_t mode);

/**
 * @brief frees mapped memory 
 * @return 0 if sucessful, 1 otherwise
 */
int (free_memory_map)(void);

/**
 * @brief copies double buffer into main video memory
 */
void (draw_double_buffer)(void);

/**
 * @brief maps vram into memory
 * @return 0 if sucessful, 1 otherwise
 */
int (map_vram)(void);

/**
 * @brief Gets bits per pixel for given mode
 * @return bits per pixel
 */
uint16_t get_bits_pixel(void);

/**
 * @brief Gets bytes per pixel for given mode
 * @return bytes per pixel
 */
uint16_t get_bytes_pixel(void);

/**
 * @brief Gets horizontal resolution for the given vbe mode
 * @return horizontal resolution
 */
uint16_t get_XRes(void);

/**
 * @brief Gets vertical resolution for the given vbe mode
 * @return vertical resolution
 */
uint16_t get_YRes(void);

/**
 * @brief Gets red mask size for the given vbe mode
 * @return red mask size
 */
uint16_t get_RedMaskSize(void);

/**
 * @brief Gets green mask size for the given vbe mode
 * @return green mask size
 */
uint16_t get_GreenMaskSize(void);

/**
 * @brief Gets blue mask size for the given vbe mode
 * @return blue mask size
 */
uint16_t get_BlueMaskSize(void);

/**
 * @brief gets physical address of flat memory frammed buffer
 * @return physical address of flat memory frammed buffer
 */
phys_bytes get_phys_addr(void);

/**
 * @brief gets Vram size of the given mode
 * @return size of the mod
 */
unsigned int get_vram_size(void);

/**
 * @brief Paints the full screen with a given color
 * @param color color to be put into the buffer
 * @return 0 if sucessful, 1 otherwise
 */
int paint_screen(uint32_t color);

/**
 * @brief clears video memory buffer
 * @return 0 if sucessful, 1 otherwise
 */
int clear_screen();

/**@}*/

#endif //GRAPHICS_H_INCLUDED
