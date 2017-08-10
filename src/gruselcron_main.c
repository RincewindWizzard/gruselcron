#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "showtime.h"
#include "video.h"

int main(int argc, char** argv) {
    char* video_file;
    char* starting_time;
    char* loop_time;
    int starting_seconds;

    if(argc != 4) {
        printf("usage: %s <video_file> <starting_time(00:00)> <loop_time(00:00)>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    video_file = argv[1];
    starting_time = argv[2];
    loop_time = argv[3];

    // checking if starting_time has right format
    if(strlen(starting_time) == 5 && starting_time[2] == ':' 
        && strlen(loop_time) == 5 && loop_time[2] == ':') {
        // inplace parsing of loop time
        loop_time[2] = 0;
        char* minutes = loop_time;
        char* seconds = minutes + 3;
        TAKTUNG = (atoi(minutes) * 60 + atoi(seconds));
        // restore
        starting_time[2] = ':';

        // inplace parsing of start time
        starting_time[2] = 0;
        minutes = starting_time;
        seconds = minutes + 3;
        starting_seconds = (atoi(minutes) * 60 + atoi(seconds)) % TAKTUNG;
        // restore
        starting_time[2] = ':';
    }
    else {
        printf("Wrong time format for Starting time (%s)\n", starting_time);
        return EXIT_FAILURE;
    }

    printf("Starting %s at %s (%d) repeating every %d seconds\n", video_file, starting_time, starting_seconds, TAKTUNG);
    start_video_loop(video_file, starting_seconds);
    return EXIT_SUCCESS;
}
