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
#define DIRECT_1280_1024_565    0x11A
#define DIRECT_1280_1024_888    0x11B
#define LINEAR_FRAME_BUFFER_MD  BIT(14)

// Color

#define BLACK 0x00000000


#endif /* end of include guard: GRAPHICS_MACROS_H_INCLUDED */
