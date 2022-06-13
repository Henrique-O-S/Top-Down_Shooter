#ifndef CROSSHAIR_H_INCLUDED
#define CROSSHAIR_H_INCLUDED

#include "graphics.h"
#include "crosshair.xpm"

static basic_sprite_t** get_crosshair(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)crosshair, 17, 17);

    return ret;
}

#endif //CROSSHAIR_H_INCLUDED
