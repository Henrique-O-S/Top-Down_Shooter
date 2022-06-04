#ifndef INTERRUPTS_H_INCLUDED
#define INTERRUPTS_H_INCLUDED

#include "libraries.h"

static int timer_id, kbc_id, mouse_id;
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

int (get_irq)(uint8_t id);

#endif //INTERRUPTS_H_INCLUDED
