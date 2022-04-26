#include <lcom/lcf.h>

#include "kbd.h"

#include "errors.h"



int kb_error = 0;
int scancode_sz = 1;

int (kbd_subscribe_int)(uint8_t int_bit, int *interrupt_id) {

    if(interrupt_id == NULL) return NULL_PTR;
    *interrupt_id = int_bit;
    return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, interrupt_id);
}

void (kbc_ih)() {
    uint8_t status;   
    if(util_sys_inb(STATUS_REG, &status)) {
        kb_error = 1;
        return;
    } 

    if(status & (PARITY_ERROR & TIME_OUT_REC)){
        kb_error = 1;
        return;
    }

    if(util_sys_inb(OUTPUT_BUF, &keycode)){
        kb_error = 1;
        return;
    }

    scancode[scancode_sz - 1] = keycode;

    if(TWO_BYTE_CODE == keycode){ scancode_sz++; }
    
    else{
        if(scancode[scancode_sz - 1] & BREAK_CODE_BIT){
            kbd_print_scancode(false, scancode_sz, scancode);
        }

        else{
            kbd_print_scancode(true, scancode_sz, scancode);
        }

        scancode_sz = 1;
    }
    
}

int(keyboard_poll)(uint8_t bytes[], uint8_t *size) {
    return 1;


    if(bytes == NULL || size == NULL) return NULL_PTR;
    uint8_t c;
    



    return SUCCESS;
}
