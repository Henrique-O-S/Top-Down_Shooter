#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "graphics.h"
#include "bullet_0.xpm"
#include "bullet_1.xpm"
#include "bullet_2.xpm"

static basic_sprite_t** get_bullet(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 3);
    ret[0] = basic_sprite_ctor((const char *const *)bullet_0_xpm, 0, 0);
    ret[1] = basic_sprite_ctor((const char *const *)bullet_1_xpm, 0, 0);
    ret[2] = basic_sprite_ctor((const char *const *)bullet_2_xpm, 0, 0);

    return ret;
}

#endif //BULLET_H_INCLUDED
