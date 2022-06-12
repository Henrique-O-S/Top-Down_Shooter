#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include "graphics.h"
#include "0.xpm"
#include "1.xpm"
#include "2.xpm"
#include "3.xpm"
#include "4.xpm"
#include "5.xpm"
#include "6.xpm"
#include "7.xpm"
#include "8.xpm"
#include "9.xpm"
#include "slash.xpm"

static basic_sprite_t** get_number(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 10);
    ret[0] = basic_sprite_ctor((const char *const *)char0_xpm, 10, 10);
    ret[1] = basic_sprite_ctor((const char *const *)char1_xpm, 10, 10);
    ret[2] = basic_sprite_ctor((const char *const *)char2_xpm, 10, 10);
    ret[3] = basic_sprite_ctor((const char *const *)char3_xpm, 10, 10);
    ret[4] = basic_sprite_ctor((const char *const *)char4_xpm, 10, 10);
    ret[5] = basic_sprite_ctor((const char *const *)char5_xpm, 10, 10);
    ret[6] = basic_sprite_ctor((const char *const *)char6_xpm, 10, 10);
    ret[7] = basic_sprite_ctor((const char *const *)char7_xpm, 10, 10);
    ret[8] = basic_sprite_ctor((const char *const *)char8_xpm, 10, 10);
    ret[9] = basic_sprite_ctor((const char *const *)char9_xpm, 10, 10);

    return ret;
}

static basic_sprite_t** get_slash(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)slash_xpm, 10, 10);

    return ret;
}

#endif //NUMBERS_H_INCLUDED
