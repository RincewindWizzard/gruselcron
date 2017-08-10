#ifndef VIDEO_H
#define VIDEO_H

#define VIDEO_PLAYER "omxplayer -o both --no-osd --loop "
//#define VIDEO_PLAYER "sh -c 'while true; do read foo; done;' #"

//#define VIDEO_PLAYER "cat > /tmp/rasp #"
#define REWIND "i"
#define STOP "q"

/* Spawns a new video player process playing the video at starting_time every TAKTUNG seconds */
void start_video_loop(char* file, int starting_time);

/* Spawns a new video player process */
void start_video(char* file);

/* Exits video playing process */
void stop_video();

/* seeks to the beginning */
void rewind_video();

#endif
