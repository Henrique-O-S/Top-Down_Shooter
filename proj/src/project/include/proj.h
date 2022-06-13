#ifndef PROJ_H_INCLUDED
#define PROJ_H_INCLUDED

/**
 * @defgroup proj proj
 * @ingroup project
 *
 * @{
 */

#include "libraries.h"
#include "sprite.h"
#include "elements.h"
#include "interrupts.h"
#include "aux_functions.h"
#include "game.h"

basic_sprite_t **bsp_crosshair;
sprite_t *sp_crosshair;

basic_sprite_t **bsp_player_idle;
basic_sprite_t **bsp_player_shooting;
basic_sprite_t **bsp_enemy_idle;
basic_sprite_t **bsp_enemy_attacking;
basic_sprite_t **bsp_bullet;

basic_sprite_t **bsp_map;
basic_sprite_t **bsp_highscore_menu;
basic_sprite_t **bsp_instructions_menu;
basic_sprite_t **bsp_gameover;
sprite_t *sp_highscore_menu;
sprite_t *sp_instructions_menu; 
sprite_t *sp_gameover;  

sprite_t *sp_map;

sprite_t *sp_player;
sprite_t *sp_enemy; 

/**
 * @}
 */

#endif //PROJ_H_INCLUDED
