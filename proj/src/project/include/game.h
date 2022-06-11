#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**
 * @defgroup game game
 * @ingroup proj
 *
 * @{
 */

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

/**
 * @}
 */
int (game_loop)();

/**
 * @}
 */
int (process_key)(const uint8_t* scancode);

#endif //GAME_H_INCLUDED
