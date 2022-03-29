#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8254.h"

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

int (kbd_ih)()
