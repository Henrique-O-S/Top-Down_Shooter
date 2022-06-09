#ifndef INTERRUPTS_H_INCLUDED
#define INTERRUPTS_H_INCLUDED

/**
 * @defgroup interrupts interrupts
 * @ingroup proj
 *
 * @{
 */

#include "libraries.h"

static int timer_subscription, keyboard_subscription, mouse_subscription;

/**
 * @brief Subscribes all drivers used (timer->keyboard->mouse)
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (subscribe_all)(void);

/**
 * @brief Unsubscribes all subscribed interrupts
 * @return Returns 0 if succeded, non 0 other wise;
 */
int (unsubscribe_all)(void);

int (get_irq)(int id);

int (get_timer_id)();

int (get_kbc_id)();

int (get_mouse_id)();

int (get_rtc_id)();

/**
 * @}
 */

#endif //INTERRUPTS_H_INCLUDED
