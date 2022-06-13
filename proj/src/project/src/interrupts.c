#include <lcom/lcf.h>

#include "interrupts.h"

static int timer_subscription = 0;

static int keyboard_subscription = 0;

static int mouse_subscription = 0;

static int rtc_subscription = 0;

int (subscribe_all)(void) {

    timer_id = 0;
    if(subscribe_timer_interrupt(TIMER0_IRQ, &timer_id)) {
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

    if(mouse_set_data_report(1)) {
        printf("%s: failed to enable mouse data report.\n", __func__);
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

    
    rtc_id = 0;
    if (subscribe_rtc_interrupt(RTC_IRQ, &rtc_id)){
        printf("%s: failed to enable rtc interrupts.\n", __func__);
        if (unsubscribe_all())
            printf("%s: failed to unsubcribe driver, unexpected behaviour is expected.\n", __func__);
        return 1;
    }
    rtc_subscription = 1;
    rtc_set_updates(1);
    

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
        if(mouse_set_data_report(0)) {
            printf("%s: failed to enable mouse data report.\n", __func__);
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

    
    if (rtc_subscription) {
        if (unsubscribe_interrupt(&rtc_id)) {
            printf("%s: failed to unsubcribe RTC interrupts.\n", __func__);
            return 1;
        }
        rtc_subscription = 0;
    }
    

    return 0;
}

int (get_irq)(int id){
    return BIT(id);
}
