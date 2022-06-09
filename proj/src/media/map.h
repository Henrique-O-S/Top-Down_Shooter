#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "graphics.h"
#include "map.xpm"

static basic_sprite_t** get_map(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)map_xpm, 0, 0);

    return ret;
}

#endif //BULLET_H_INCLUDED
