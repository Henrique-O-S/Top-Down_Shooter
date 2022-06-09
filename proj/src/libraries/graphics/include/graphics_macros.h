#ifndef GRAPHICS_MACROS_H_INCLUDED
#define GRAPHICS_MACROS_H_INCLUDED

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

#define MAP_COL0 0x1b2901
#define MAP_COL1 0x1b3a01
#define MAP_COL2 0x1b4a01
#define MAP_COL3 0x1b5901
#define MAP_COL4 0x1b6801
#define MAP_COL5 0x1b7701
#define MAP_COL6 0x1b8801
#define MAP_COL7 0x1b9801
#define MAP_COL8 0x1ba901
#define MAP_COL9 0x6aa900
#define MAP_COL10 0x6ab900
#define MAP_COL11 0x9cb901
#define MAP_COL12 0xb9d503
#define MAP_COL13 0xb9fa03


#endif /* end of include guard: GRAPHICS_MACROS_H_INCLUDED */
