#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

//Subscribe timer interrupts
int (timer_subscribe_int___)();

//Unsubscribe timer interrupts
int (timer_unsubscribe_int)();

//Uses timer to sleep for "time" seconds
int (_timer_sleep_)(int time);

#endif /* __TIMER_H */
