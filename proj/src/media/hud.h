#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "graphics.h"
#include "hud.xpm"

static basic_sprite_t** get_hud(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 1);
    ret[0] = basic_sprite_ctor((const char *const *)hud_xpm, 0, 0);

    return ret;
}

#endif //HUD_H_INCLUDED
