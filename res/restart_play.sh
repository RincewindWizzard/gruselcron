#!/bin/bash
video="/home/pi/videos/Textvideo Synchro.mp4"

killall omxplayer.bin
omxplayer -o hdmi "$video"
