#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8254.h"
#include "kbc_macros.h"

uint8_t scancode[2];
uint8_t keycode;
int keyboard_done;
int kb_error;
int scancode_sz;

int (kbd_subscribe_int)(uint8_t int_bit, int *interrupt_id);
int keyboard_done;
int scancode_sz;

void (kbd_ih)();
