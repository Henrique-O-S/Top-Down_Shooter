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
int (game_display)(keys_t *keys);

/**
 * @}
 */
int (process_key)(const uint8_t* scancode);

#endif //GAME_H_INCLUDED
