#include <lcom/lcf.h>

#include "kbc.h"
#include "utils.h"
#include "errors.h"

int (kbd_unsubscribe_int)(int *interrupt_id) {

    if(interrupt_id == NULL) return NULL_PTR;
    return sys_irqrmpolicy(interrupt_id);
}

int (kbc_restore_keyboard)(){

    return 0;
}
