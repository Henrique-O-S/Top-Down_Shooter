#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

/**
 * @defgroup timer timer
 * @ingroup libraries
 *
 * @{
 */

#include <lcom/lcf.h>

uint32_t no_interrupts;

/**
 * @brief Subscribes interrupt bit for timer
 * @param interrupt_bit interrupt bit
 * @param interrupt_id pointer for the interrupt bit to be used
 * @return 0 if sucessful, 1 otherwise 
 */
int (subscribe_timer_interrupt)(uint8_t interrupt_bit, int *interrupt_id);

/**
 * @brief Increments the number of interrupts
 * 
 */
void (timer_int_handler)();

/**
 * @brief Gets number of interrupts
 * @return number of interrupts
 */
uint32_t (get_no_interupts)();

/**
 * @brief Sets number of interrupts for a given value
 * @param n new number for the number of interrupts
 */
void (set_no_interupts)(uint32_t n);

/**@}*/

#endif //TIMER_H_INCLUDED
