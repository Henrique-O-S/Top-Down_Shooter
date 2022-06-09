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
#include "survivor-shoot_rifle_0.xpm"
#include "survivor-shoot_rifle_1.xpm"
#include "survivor-shoot_rifle_2.xpm"



static basic_sprite_t** get_player_idle(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 20);
    ret[0] = basic_sprite_ctor((const char *const *)survivor_move_rifle_0_xpm, 64, 75);
    ret[1] = basic_sprite_ctor((const char *const *)survivor_move_rifle_1_xpm, 64, 75);
    ret[2] = basic_sprite_ctor((const char *const *)survivor_move_rifle_2_xpm, 64, 75);
    ret[3] = basic_sprite_ctor((const char *const *)survivor_move_rifle_3_xpm, 64, 75);
    ret[4] = basic_sprite_ctor((const char *const *)survivor_move_rifle_4_xpm, 64, 75);
    ret[5] = basic_sprite_ctor((const char *const *)survivor_move_rifle_5_xpm, 64, 75);
    ret[6] = basic_sprite_ctor((const char *const *)survivor_move_rifle_6_xpm, 64, 75);
    ret[7] = basic_sprite_ctor((const char *const *)survivor_move_rifle_7_xpm, 64, 75);
    ret[8] = basic_sprite_ctor((const char *const *)survivor_move_rifle_8_xpm, 64, 75);
    ret[9] = basic_sprite_ctor((const char *const *)survivor_move_rifle_9_xpm, 64, 75);
    ret[10] = basic_sprite_ctor((const char *const *)survivor_move_rifle_10_xpm, 64, 75);
    ret[11] = basic_sprite_ctor((const char *const *)survivor_move_rifle_11_xpm, 64, 75);
    ret[12] = basic_sprite_ctor((const char *const *)survivor_move_rifle_12_xpm, 64, 75);
    ret[13] = basic_sprite_ctor((const char *const *)survivor_move_rifle_13_xpm, 64, 75);
    ret[14] = basic_sprite_ctor((const char *const *)survivor_move_rifle_14_xpm, 64, 75);
    ret[15] = basic_sprite_ctor((const char *const *)survivor_move_rifle_15_xpm, 64, 75);
    ret[16] = basic_sprite_ctor((const char *const *)survivor_move_rifle_16_xpm, 64, 75);
    ret[17] = basic_sprite_ctor((const char *const *)survivor_move_rifle_17_xpm, 64, 75);
    ret[18] = basic_sprite_ctor((const char *const *)survivor_move_rifle_18_xpm, 64, 75);
    ret[19] = basic_sprite_ctor((const char *const *)survivor_move_rifle_19_xpm, 64, 75);

    return ret;
}

static basic_sprite_t** get_player_shooting(void) {
    basic_sprite_t** ret = (basic_sprite_t**)malloc(sizeof(basic_sprite_t*) * 3);
    ret[0] = basic_sprite_ctor((const char *const *)survivor_shoot_rifle_0_xpm, 64, 75);
    ret[1] = basic_sprite_ctor((const char *const *)survivor_shoot_rifle_1_xpm, 64, 75);
    ret[2] = basic_sprite_ctor((const char *const *)survivor_shoot_rifle_2_xpm, 64, 75);

    return ret;
}

#endif //PLAYER_H_INCLUDED
