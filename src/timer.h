#ifndef TIMER_H
#define TIMER_H


/* Signal Handler */
void on_sigalrm();
void on_sigint();

/* Starts timer to fire SIGALRM every Taktung seconds */
void start_timer(int starting_time, void (*on_interval)(int), void (*on_ex)(void));

/* This is blocking the main Thread from exiting the process */
#include <semaphore.h>
sem_t exit_condition;

#endif
