/**
 * This file concerns everything related to the keyboard
 */
#include <lcom/lcf.h>

#ifndef KBD_H_INCLUDED
#define KBD_H_INCLUDED

int (subscribe_kbc_interrupt)(uint8_t interrupt_bit, int *interrupt_id);

uint8_t scancode[2];
int done;
int sz;
int got_error_keyboard;

void (kbc_ih)(void);

int (keyboard_poll)(uint8_t bytes[], uint8_t *size);

uint8_t (get_scancode)(int i);

#endif //KBD_H_INCLUDED