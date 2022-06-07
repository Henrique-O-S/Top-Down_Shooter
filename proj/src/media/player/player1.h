#ifndef PLAYER1_H_INCLUDED
#define PLAYER1_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_5.xpm"

static basic_sprite_t* get_player1(void) {
    return basic_sprite_ctor((const char *const *)survivor_move_rifle_5_xpm, 0, 0);
}

#endif //PLAYER_H_INCLUDED
