#ifndef PROJ_H_INCLUDED
#define PROJ_H_INCLUDED

#include "libraries.h"
#include "elements.h"
#include "interrupts.h"
#include "aux_functions.h"


basic_sprite_t **bsp_player_idle;
basic_sprite_t **bsp_player_shooting;
basic_sprite_t **bsp_enemy_idle;
basic_sprite_t **bsp_enemy_attacking;
basic_sprite_t **bsp_bullet;

basic_sprite_t **bsp_map;
sprite_t *sp_map;


//basic_sprite_t **bsp_player;
//basic_sprite_t **bsp_enemy;

sprite_t *sp_player;
sprite_t *sp_enemy; 


basic_sprite_t **bsp_crosshair;
sprite_t *sp_crosshair;
#endif //PROJ_H_INCLUDED
