#include <lcom/lcf.h>

#include "kbd.h"

#include "errors.h"


int (kbd_subscribe_int)(uint8_t *interrupt_id) {

    if(interrupt_id == NULL) return NULL_PTR;

    return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &interrupt_id);
}

int (kbd_unsubscribe_int)(uint8_t *interrupt_id) {
  return sys_irqrmpolicy(&interrupt_id);
}

int kb_error = 0;

void kbc_ih() {
    uint8_t status;   
    if(util_sys_inb(STATUS_REG, &status)) {
        kb_error = 1;
        return;
    } 
}
