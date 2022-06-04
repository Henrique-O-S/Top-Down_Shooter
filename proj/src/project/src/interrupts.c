#include <lcom/lcf.h>

#include "interrupts.h"

static int timer_subscription = 0, timer_id;

static int keyboard_subscription = 0, kbc_id;

static int mouse_subscription = 0, mouse_id;

int (subscribe_all)(void) {

    timer_id = 0;
    if(subscribe_timer_interrupt(&timer_id)) {
        printf("%s: failed to subscribe timer interrupts.\n", __func__);
        return 1;
    }
    timer_subscription = 1;

    kbc_id = 0;
    if (subscribe_kbc_interrupt(KBC_IRQ, &kbc_id)) {
        printf("%s: failed to subscribe keyboard interrupts.\n", __func__);
        if (unsubscribe_all())
            printf("%s: failed to unsubcribe interrupts\n", __func__);
        return 1;
    }
    keyboard_subscription = 1;

    mouse_id = 0;
    if (mouse_subscribe_int(MOUSE_IRQ, &mouse_id)) {
        printf("%s: failed to subscribe mouse interrupts.\n", __func__);
        if (unsubscribe_all())
            printf("%s: failed to unsubcribe interrupts\n", __func__);        
        return 1;
    }
    mouse_subscription = 1;

    if (sys_irqdisable(&mouse_id)) {
        printf("%s: failed to disable mouse interrupts.\n", __func__);
        if (unsubscribe_all())
            printf("%s: failed to unsubcribe interrupts\n", __func__); 
        return 1;
    }
    
    if (sys_irqenable(&mouse_id)) {
        printf("%s: failed to enable mouse interrupts.\n", __func__);
        if (unsubscribe_all())
            printf("%s: failed to unsubcribe interrupts\n", __func__);
        return 1;
    }

    return 0;
}

int (unsubscribe_all)(void) {

    if (timer_subscription) {
        if (unsubscribe_interrupt(&timer_id)) {
            printf("%s: failed to unsubcribe timer interrupts.\n", __func__);
            return 1;
        }
        timer_subscription = 0;
    }

    if (keyboard_subscription) {
        if (unsubscribe_interrupt(&kbc_id)) {
            printf("%s: failed to unsubcribe keyboard interrupts.\n", __func__);
            return 1;
        }
        keyboard_subscription = 0;
    }

    if (mouse_subscription) {
        if (sys_irqdisable(&mouse_id)) {
            printf("%s: failed to disable mouse interrupts.\n", __func__);
            return 1;
        }
        if (sys_irqenable(&mouse_id)) {
            printf("%s: failed to enable mouse interrupts.\n", __func__);
            return 1;
        }
        if (mouse_unsubscribe_int(&mouse_id)) {
            printf("%s: failed to unsubcribe mouse interrupts.\n", __func__);
            return 1;
        }
        mouse_subscription = 0;
    }

    return 0;
}
