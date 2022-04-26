#include <lcom/lcf.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"

static int timer_hook; //Timer 0 hook id

//Subscribe timer interrupts
int (timer_subscribe_int___)() {
	timer_hook = 2;
    if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook) == OK) {
    	if (sys_irqenable(&timer_hook) == OK) {
#if defined(DEBUG) && DEBUG == 1
    		printf("Hook id returned: 0x%02X\n\n", timer_hook);
#endif
    		return 2;
    	} else {
    		printf("timer: timer_subcribe_int failed to enable interrupts\n");
    		return -1;
    	}
    } else {
    	printf("timer: timer_subscribe_int failed to set policy\n");
    	return -1;
    }
}


//Unsubscribe timer interrupts
int (timer_unsubscribe_int)() {
    if(sys_irqdisable(&timer_hook) == OK) {
    	if(sys_irqrmpolicy(&timer_hook) == OK) {
    		return 0;
    	} else {
    		printf("timer: timer_unsubscribe_int failed to disable policy\n");
    		return -1;
    	}
    } else {
    		printf("timer: timer_unsubscribe_int failed to disable interrupts\n");
    		return -1;
    }
}


//Uses timer to sleep for "time" seconds
int (_timer_sleep_)(int time) {

	//Subscribe timer interrupts
	int hook = timer_subscribe_int___();
	int counter = 0;

	if (hook >= 0) { //Check if valid hook id

		//Variables for interrupt handling
		int ipc_status, dstatus;
		message msg;
		int irq_set = BIT(hook); //bitmask for timer interrupts
		float freq = 60; //Frequency used by the timer interrupt

		//Interrupt handling
		while(counter < time * freq) { //counter is updated at freq/s so we multiply freq * time to get counter value at time (seconds)
			if ((dstatus = driver_receive(ANY, &msg, &ipc_status)) != 0) { //Receives any messages
				printf("driver_receive failed with: %d", dstatus);
				continue;
			}

			//Check if notification
			if (is_ipc_notify(ipc_status)) {
			//Debug info for notifications and interrupt bitmask
				switch (_ENDPOINT_P(msg.m_source)) {
					case HARDWARE: //Hardware interrupt notification
						if (msg.m_notify.interrupts & irq_set) { //Bitmask hook id to check for timer interrupt
							counter++;
						}
						break;

					default: //No other notifications expected, do nothing
						break;
				}
			} else {
				//Debug info for standard message reception
				}
		}

		//Reset parameters
		counter = 0;

		//Unsubscribe timer interrupts
		if (timer_unsubscribe_int() == 0) {
			return 0;
		} else return -1; //Failed to unsubscribe timer interrupts
	} else return -1; //Failed to subscribe timer interrupts
}
