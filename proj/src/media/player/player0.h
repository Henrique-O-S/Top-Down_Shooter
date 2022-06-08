#ifndef PLAYER0_H_INCLUDED
#define PLAYER0_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_0_0.xpm"

static basic_sprite_t* get_player0(void) {
    return basic_sprite_ctor((const char *const *)survivor_move_rifle_0_0_xpm, 100, -400);
}

#endif //PLAYER_H_INCLUDED
