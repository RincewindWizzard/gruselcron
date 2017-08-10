#include <sys/sysinfo.h>
#include <stdio.h>
#include "showtime.h"

void print_showtime() {
    int time = showtime();
    printf("[%02d:%02d]", (time / 60), (time % 60));
}

/* Berechnet die aktuelle Zeit in der Show */
int showtime() {
    struct sysinfo info;
    sysinfo(&info);
    int showtime = info.uptime % TAKTUNG;
    return showtime;
}
