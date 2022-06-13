#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include "graphics.h"
#include "gameover.xpm"

static basic_sprite_t** get_gameover(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)gameover_xpm, 0, 0);

    return ret;
}

#endif //GAMEOVER_H_INCLUDED
