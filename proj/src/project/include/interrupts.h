#ifndef INTERRUPTS_H_INCLUDED
#define INTERRUPTS_H_INCLUDED

#include "libraries.h"

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

#endif //INTERRUPTS_H_INCLUDED
