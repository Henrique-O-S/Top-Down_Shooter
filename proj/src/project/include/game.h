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

/**
 * @}
 */
/**
 * @brief Displays all in game elements (players, monsters, bullets, ...)
 * @return Returns 0 if succeded, 1 other wise;
 */
int (game_display)(keys_t *keys);

/**
 * @}
 */
int (process_key)(const uint8_t* scancode);

/**
 * @}
 */
/**
 * @brief Dispawns all in game elements
 */
void(game_dispawn_everyting());


#endif //GAME_H_INCLUDED
