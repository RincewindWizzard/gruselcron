#!/usr/bin/python
# -*- coding: utf-8 -*-
import re, os,subprocess
vid_path = "/mnt/"
name_pattern = re.compile(r'.*(?P<minutes>\d\d)(?P<seconds>\d\d)\....$')


for path in os.listdir(vid_path):
    if os.path.isfile(vid_path + path):
        m = name_pattern.match(path)
        if m:
                cmd = ["gruselcron", vid_path+path,  (m.group("minutes") + ":" + m.group("seconds"))]
                print cmd
                subprocess.call(cmd)
                exit(0)

subprocess.call(["/usr/bin/fbi", "-T", "1", "-noverbose",  "/var/share/gruselpi/no_video.png"])
exit(1)
