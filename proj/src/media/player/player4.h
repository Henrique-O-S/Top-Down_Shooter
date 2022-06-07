#ifndef PLAYER4_H_INCLUDED
#define PLAYER4_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_19.xpm"

static basic_sprite_t* get_player4(void) {
    return basic_sprite_ctor((const char *const *)survivor_move_rifle_19_xpm, 0, 0);
}

#endif //PLAYER_H_INCLUDED
