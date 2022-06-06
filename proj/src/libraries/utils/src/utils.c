#include <lcom/lcf.h>

#include "../include/utils.h"

#include <stdint.h>
#include <math.h>

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

double fm_sin(double x){
    if(x < 0.0)         return -fm_sin(-x);
    if(x > 2.0*M_PI) return fm_sin(x-2.0*M_PI);
    if(x > M_PI)      return -fm_sin(x-M_PI);
    if(x > 0.5*M_PI) x = M_PI - x;
    double x2 = x*x;
    double x3 = x*x2;
    double x5 = x3*x2;
    //double x7 = x5*x2;
    return x-x3*0.1666666666666666666666+x5*0.008333333333333333333333;
}

double fm_cos(double x){
    if(x < 0.0)         x = -x;
    if(x > 2.0*M_PI) return fm_cos(x-2.0*M_PI);
    if(x > M_PI)      x = 2.0*M_PI-x;
    if(x > 0.5*M_PI) return -fm_cos(M_PI-x);
    double x2 = x*x;
    double x4 = x2*x2;
    double x6 = x4*x2;
    //double x8 = x4*x4;
    return 1.0-x2*0.5+x4*0.041666666666666666666666-x6*0.0013888888888888888888888;
}
