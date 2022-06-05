/**
 * This file concerns everything related to the timer
 */
#include <lcom/lcf.h>

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

uint32_t no_interrupts;

int (subscribe_timer_interrupt)(uint8_t interrupt_bit, int *interrupt_id);
void (timer_int_handler)();

#endif //TIMER_H_INCLUDED
