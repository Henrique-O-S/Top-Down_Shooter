#ifndef AUX_FUNCTIONS_H_INCLUDED
#define AUX_FUNCTIONS_H_INCLUDED

/**
 * @defgroup aux_functions aux_functions
 * @ingroup proj
 *
 * @{
 */

#include "libraries.h"

int (menu_init)();

uint16_t (mouse_in_box)();

int (process_mouse)(struct packet *p);

/**
 * @}
 */
int (map1_init)();

void (map1_background)(void);

#endif //AUX_FUNCTIONS_H_INCLUDED
