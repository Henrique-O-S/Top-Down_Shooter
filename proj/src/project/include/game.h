#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**
 * @defgroup game game
 * @ingroup project
 *
 * @{
 */

#include "libraries.h"
#include "elements.h"
#include "interrupts.h"
#include "aux_functions.h"

/**
 * @brief Displays everything in the game state and updates game state
 */
int (game_display)(keys_t *keys);

/**
 * @brief Sets up HUD and highscore for game
 */
void(game_place_everything)();

/**
 * @brief Despawns all objects relative to the game when it ends
 */
void(game_despawn_everyting)();

/**
 * @brief Displays the score at the end of the game
 */
void(display_score)();

/**
 * @}
 */

#endif //GAME_H_INCLUDED
