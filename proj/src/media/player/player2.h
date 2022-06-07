#ifndef PLAYER2_H_INCLUDED
#define PLAYER2_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_10.xpm"

static basic_sprite_t* get_player2(void) {
    return basic_sprite_ctor((const char *const *)survivor_move_rifle_10_xpm, 0, 0);
}

#endif //PLAYER_H_INCLUDED
