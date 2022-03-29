#include <lcom/lcf.h>

#include "kbd.h"

#include <stdint.h>

#include "i8254.h"
#include "errors.h"


static int hook_id;

int (kbd_subscribe_int)(uint8_t *bit_no) {

    if(bit_no == NULL) return NULL_PTR;
    hook_id = 2;
    *bit_no = hook_id;

    return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}
int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

int kbh_ih(){
    
}
