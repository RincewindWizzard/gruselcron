#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "video.h"
#include "timer.h"
#include "showtime.h"

char* video_file;
FILE *video_process;

/* Spawns a new video player process */
void start_video(char* file) {
    char cmd[strlen(VIDEO_PLAYER) + strlen(file) + 1];
    strcpy(cmd,VIDEO_PLAYER);
    strcat(cmd,file);

    video_process = popen(cmd, "w");
    print_showtime();
    printf(" Starting video \"%s\"\n", cmd);
}

/* Exits video playing process */
void stop_video() {
    print_showtime();
    printf(" Stop video\n");
    fprintf(video_process, STOP);
    fflush(video_process);
    pclose(video_process);
}

/* seeks to the beginning */
void rewind_video() {
    if(video_process) {
        print_showtime();
        printf(" Rewind Video %s\n", video_file);
        fprintf(video_process, REWIND);
        fflush(video_process);
    }
    else {
        start_video(video_file);
    }
}

/* Spawns a new video player process playing the video at starting_time every TAKTUNG seconds */
void start_video_loop(char* file, int starting_time) {
    video_file = file;
    start_timer(starting_time, rewind_video, stop_video);
}

