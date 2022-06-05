#include <lcom/lcf.h>

#include "../include/utils.h"

#include <stdint.h>

int (unsubscribe_interrupt)(int *interrupt_id) {
    if (interrupt_id == NULL) return 1;
    if(sys_irqrmpolicy(interrupt_id)) return 1;
    return 0;
}

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
    if (lsb == NULL) return 1;
    *lsb = val;
    return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
    if (msb == NULL) return 1;
    *msb = (val >> 8);
    return 0;
}

#ifdef LAB3
    uint32_t sys_inb_counter = 0;
#endif

int (util_sys_inb)(int port, uint8_t *value) {
    if(value == NULL) return 1;
    uint32_t n = 0;
    if(sys_inb(port, &n)) return 1;
    *value = n;
    #ifdef LAB3
        ++sys_inb_counter;
    #endif
    return 0;
}

int16_t abs16(int16_t x) {
    return (x >= 0) ? (int16_t)(x) : (int16_t)(-x);
}

int16_t min(int16_t a, int16_t b){ return (b < a ? b : a); }
int16_t max(int16_t a, int16_t b){ return (a < b ? b : a); }
