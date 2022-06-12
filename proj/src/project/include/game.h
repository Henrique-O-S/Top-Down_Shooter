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

int (game_display)(keys_t *keys);

void(game_place_everything)();

void(game_dispawn_everyting)();

void(display_score)();

/**
 * @}
 */

#endif //GAME_H_INCLUDED
