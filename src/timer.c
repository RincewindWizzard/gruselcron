#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <semaphore.h>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 

#include "timer.h"
#include "showtime.h"

void (*on_stop)(void);

void on_sigterm() {
    on_stop();
    print_showtime();
    printf(" SIGTERM\n");
    sem_post(&exit_condition);
}

/* Starts timer to fire SIGALRM everytime showtime exceeds eventtime */
void start_timer(int starting_time, void (*on_interval)(int), void (*on_ex)(void)) {
    on_stop = on_ex;

    int seconds_until = starting_time - showtime();
    while(seconds_until < 1) seconds_until += TAKTUNG;

    // setting up timer
    struct itimerval tout_val;
    tout_val.it_interval.tv_sec = TAKTUNG;
    tout_val.it_interval.tv_usec = 0;
    tout_val.it_value.tv_sec = seconds_until;
    tout_val.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &tout_val,0);

    if (signal(SIGALRM, on_interval) == SIG_ERR) {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (signal(SIGTERM, on_sigterm) == SIG_ERR) {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // Blocking until SIGINT is catched
    sem_init(&exit_condition, 0, 0);
    sem_wait(&exit_condition);
    sem_destroy(&exit_condition);
}
