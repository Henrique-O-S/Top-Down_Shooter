#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include "graphics.h"
#include "highscore_table.xpm"

static basic_sprite_t** get_highscore(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)highscore_table_xpm, 0, 0);

    return ret;
}

#endif //HIGHSCORE_H_INCLUDED
