#ifndef PLAYER3_H_INCLUDED
#define PLAYER3_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_15.xpm"

static basic_sprite_t* get_player3(void) {
    return basic_sprite_ctor((const char *const *)survivor_move_rifle_15_xpm, 0, 0);
}

#endif //PLAYER_H_INCLUDED
