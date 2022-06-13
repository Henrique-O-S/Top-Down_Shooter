#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "graphics.h"
#include "play1.xpm"
#include "play2.xpm"
#include "exit1.xpm"
#include "exit2.xpm"
#include "highscore1.xpm"
#include "highscore2.xpm"
#include "instructions1.xpm"
#include "instructions2.xpm"


static basic_sprite_t** get_play(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 2);
    ret[0] = basic_sprite_ctor((const char *const *)play1_xpm, 0, 0);
    ret[1] = basic_sprite_ctor((const char *const *)play2_xpm, 0, 0);

    return ret;
}

static basic_sprite_t** get_exit(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 2);
    ret[0] = basic_sprite_ctor((const char *const *)exit1_xpm, 0, 0);
    ret[1] = basic_sprite_ctor((const char *const *)exit2_xpm, 0, 0);

    return ret;
}

static basic_sprite_t** get_highscore(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 2);
    ret[0] = basic_sprite_ctor((const char *const *)highscore1_xpm, 0, 0);
    ret[1] = basic_sprite_ctor((const char *const *)highscore2_xpm, 0, 0);

    return ret;
}

static basic_sprite_t** get_instructions(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 2);
    ret[0] = basic_sprite_ctor((const char *const *)instructions1_xpm, 0, 0);
    ret[1] = basic_sprite_ctor((const char *const *)instructions2_xpm, 0, 0);

    return ret;
}

#endif //MENU_H_INCLUDED
