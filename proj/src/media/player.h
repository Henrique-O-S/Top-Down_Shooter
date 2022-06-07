#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_0.xpm"
#include "player.xpm"

static basic_sprite_t* get_player(void) {
    return basic_sprite_ctor((const char *const *)survivor_move_rifle_0_xpm, 0, 0);
}

#endif //PLAYER_H_INCLUDED
