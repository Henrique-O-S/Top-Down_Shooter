#ifndef KBD_H_INCLUDED
#define KBD_H_INCLUDED

/**
 * @defgroup kbd kbd
 * @ingroup libraries
 *
 * @{
 */

#include <lcom/lcf.h>

int (subscribe_kbc_interrupt)(uint8_t interrupt_bit, int *interrupt_id);

uint8_t scancode[2];
int done;
int sz;
int got_error_keyboard;

void (kbc_ih)(void);

int (keyboard_poll)(uint8_t bytes[], uint8_t *size);

const uint8_t* (get_scancode)();

/**@}*/

#endif //KBD_H_INCLUDED
