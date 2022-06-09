#ifndef PLAYER0_H_INCLUDED
#define PLAYER0_H_INCLUDED

#include "graphics.h"
#include "survivor-move_rifle_0.xpm"
#include "survivor-move_rifle_1.xpm"
#include "survivor-move_rifle_2.xpm"
#include "survivor-move_rifle_3.xpm"
#include "survivor-move_rifle_4.xpm"
#include "survivor-move_rifle_5.xpm"
#include "survivor-move_rifle_6.xpm"
#include "survivor-move_rifle_7.xpm"
#include "survivor-move_rifle_8.xpm"
#include "survivor-move_rifle_9.xpm"
#include "survivor-move_rifle_10.xpm"
#include "survivor-move_rifle_11.xpm"
#include "survivor-move_rifle_12.xpm"
#include "survivor-move_rifle_13.xpm"
#include "survivor-move_rifle_14.xpm"
#include "survivor-move_rifle_15.xpm"
#include "survivor-move_rifle_16.xpm"
#include "survivor-move_rifle_17.xpm"
#include "survivor-move_rifle_18.xpm"
#include "survivor-move_rifle_19.xpm"


static basic_sprite_t** get_player(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 20);
    ret[0] = basic_sprite_ctor((const char *const *)survivor_move_rifle_0_xpm, 100, 0);
    ret[1] = basic_sprite_ctor((const char *const *)survivor_move_rifle_1_xpm, 100, 0);
    ret[2] = basic_sprite_ctor((const char *const *)survivor_move_rifle_2_xpm, 100, 0);
    ret[3] = basic_sprite_ctor((const char *const *)survivor_move_rifle_3_xpm, 100, 0);
    ret[4] = basic_sprite_ctor((const char *const *)survivor_move_rifle_4_xpm, 100, 0);
    ret[5] = basic_sprite_ctor((const char *const *)survivor_move_rifle_5_xpm, 100, 0);
    ret[6] = basic_sprite_ctor((const char *const *)survivor_move_rifle_6_xpm, 100, 0);
    ret[7] = basic_sprite_ctor((const char *const *)survivor_move_rifle_7_xpm, 100, 0);
    ret[8] = basic_sprite_ctor((const char *const *)survivor_move_rifle_8_xpm, 100, 0);
    ret[9] = basic_sprite_ctor((const char *const *)survivor_move_rifle_9_xpm, 100, 0);
    ret[10] = basic_sprite_ctor((const char *const *)survivor_move_rifle_10_xpm, 100, 0);
    ret[11] = basic_sprite_ctor((const char *const *)survivor_move_rifle_11_xpm, 100, 0);
    ret[12] = basic_sprite_ctor((const char *const *)survivor_move_rifle_12_xpm, 100, 0);
    ret[13] = basic_sprite_ctor((const char *const *)survivor_move_rifle_13_xpm, 100, 0);
    ret[14] = basic_sprite_ctor((const char *const *)survivor_move_rifle_14_xpm, 100, 0);
    ret[15] = basic_sprite_ctor((const char *const *)survivor_move_rifle_15_xpm, 100, 0);
    ret[16] = basic_sprite_ctor((const char *const *)survivor_move_rifle_16_xpm, 100, 0);
    ret[17] = basic_sprite_ctor((const char *const *)survivor_move_rifle_17_xpm, 100, 0);
    ret[18] = basic_sprite_ctor((const char *const *)survivor_move_rifle_18_xpm, 100, 0);
    ret[19] = basic_sprite_ctor((const char *const *)survivor_move_rifle_19_xpm, 100, 0);

    return ret;
}

#endif //PLAYER_H_INCLUDED
