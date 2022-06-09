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

int (game_loop)();

int (process_key_game)(const uint8_t* scancode);

/**
 * @}
 */

#endif //GAME_H_INCLUDED
