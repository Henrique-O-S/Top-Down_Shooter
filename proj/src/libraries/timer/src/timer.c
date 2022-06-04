#include <lcom/lcf.h>

#include <stdint.h>

#include "i8254.h"

static int hook_id;

int (subscribe_timer_interrupt)(int *bit_no) {
    if(bit_no == NULL) return 1;
    hook_id = 2;
    *bit_no = hook_id;
    return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);

  return 1;
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

uint32_t no_interrupts = 0;
void (timer_int_handler)() {
  no_interrupts++;
}
