#include <lcom/lcf.h>

#include "kbd.h"

#include "errors.h"

uint8_t keycode;

int (kbd_subscribe_int)(uint8_t *interrupt_id) {

    if(interrupt_id == NULL) return NULL_PTR;

    return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &interrupt_id);
}

int (kbd_unsubscribe_int)(uint8_t *interrupt_id) {
  return sys_irqrmpolicy(&interrupt_id);
}

int kb_error = 0;
int keyboard_done = 1;
int scancode_sz = 1;

void kbc_ih() {
    uint8_t status;   
    if(util_sys_inb(STATUS_REG, &status)) {
        kb_error = 1;
        return;
    } 

    if(status & (PARITY_ERROR & TIME_OUT_REC)){
        kb_error = 1;
        return;
    }

    else{
        util_sys_inb(OUTPUT_BUF, &keycode);
    }
    scancode[scancode_sz] = byte;
    scancode_sz++;
    keyboard_done = !(TWO_BYTE_CODE == byte);
    
}
