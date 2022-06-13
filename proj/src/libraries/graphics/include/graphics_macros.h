#ifndef GRAPHICS_MACROS_H_INCLUDED
#define GRAPHICS_MACROS_H_INCLUDED

/** @defgroup graphics_macros graphics_macros
 * @ingroup libraries
 * @{
 *
 * Constants for programming the Mouse.
 */

// Bios Services/Calls

#define VC_BIOS_SERV  0x10 /** @brief Video Card interrupt vector */
#define VBE_CALL 0x4F /** @brief VBE Call */


// Graphics Functions
#define VBE_CTRL_INFO 0x00 /** @brief Set VBE Mode */
#define VBE_MD_INFO 0x01 /** @brief Set VBE Mode */
#define FUNC_02 0x02 /** @brief Set VBE Mode */


// Graphics modes
#define INDEXED_1024_768        0x105
#define DIRECT_640_480          0x110
#define DIRECT_800_600          0x115
#define DIRECT_1024_768_888     0x118
#define DIRECT_1280_1024_565    0x11A
#define DIRECT_1280_1024_888    0x11B
#define LINEAR_FRAME_BUFFER_MD  BIT(14)

// Color

#define BLACK 0x00000000
#define MENU_BACKGROUND_COLOR 0x0ABAB5
#define MENU_OPTION_COLOR 0xFF0000
#define PLAY_COLOR 0x93c47d
#define EXIT_COLOR 0x93c47d
#define SELECTED_COLOR 0xffff00

#define MAP_COL01 0x030400
#define MAP_COL02 0x080a00
#define MAP_COL03 0x0b0f00
#define MAP_COL04 0x0f1400
#define MAP_COL05 0x131a00
#define MAP_COL06 0x171f00
#define MAP_COL07 0x182100
#define MAP_COL08 0x1a2400
#define MAP_COL09 0x1e2900
#define MAP_COL10 0x222e00
#define MAP_COL11 0x263301
#define MAP_COL12 0x293801
#define MAP_COL13 0x2d3d01
#define MAP_COL14 0x314201
#define MAP_COL15 0x354701
#define MAP_COL16 0x384d01
#define MAP_COL17 0x3c5201
#define MAP_COL18 0x405701
#define MAP_COL19 0x445c01
#define MAP_COL20 0x476101
#define MAP_COL21 0x4b6601
#define MAP_COL22 0x4f6b01
#define MAP_COL23 0x537001
#define MAP_COL24 0x567501
#define MAP_COL25 0x5a7a01
#define MAP_COL26 0x5e8001
#define MAP_COL27 0x628501
#define MAP_COL28 0x658a01
#define MAP_COL29 0x698f01
#define MAP_COL30 0x6d9401
#define MAP_COL31 0x719902
#define MAP_COL32 0x749e02
#define MAP_COL33 0x78a302
#define MAP_COL34 0x7aa602
#define MAP_COL35 0x7ca802
#define MAP_COL36 0x7eab02
#define MAP_COL37 0x80ad02
#define MAP_COL38 0x81b002
#define MAP_COL39 0x83b302
#define MAP_COL40 0x85b502
#define MAP_COL41 0x87b802
#define MAP_COL42 0x8bbd02
#define MAP_COL43 0x8fc202
#define MAP_COL44 0x91c402
#define MAP_COL45 0x92c702
#define MAP_COL46 0x94c902
#define MAP_COL47 0x96cc02
#define MAP_COL48 0x9ad102
#define MAP_COL49 0x9ed602
#define MAP_COL50 0xa1db02
#define MAP_COL51 0xa5e002
#define MAP_COL52 0xa9e502
#define MAP_COL53 0xadeb02
#define MAP_COL54 0xafed02
#define MAP_COL55 0xb0f002
#define MAP_COL56 0xb4f502
#define MAP_COL57 0xb6f702
#define MAP_COL58 0xb8fa02
#define MAP_COL59 0xbafc03
#define MAP_COL60 0xbcff03

/**
 * @}
 */


#endif //GRAPHICS_MACROS_H_INCLUDED
