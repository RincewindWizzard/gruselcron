#!/usr/bin/python3
# -*- coding: utf-8 -*-
import re, os,subprocess
vid_path = "/mnt/"
name_pattern = re.compile(
  r'.*(?P<starttime_minutes>\d\d)(?P<starttime_seconds>\d\d)_(?P<intervall_minutes>\d\d)(?P<intervall_seconds>\d\d)\....$'
)

def log(msg):
  try:
    with open('/dev/tty1', 'w') as f:
      f.write(msg)
      f.write('\n')
  except:
    print(msg)

log('Looking for video files in /mnt/')
for path in os.listdir(vid_path):
  log('Found' + path)
  if os.path.isfile(vid_path + path):
    m = name_pattern.match(path)
    if m:
      cmd = [
        "gruselcron",
        vid_path+path,
        '{}:{}'.format(
          m.group("starttime_minutes"),
          m.group("starttime_seconds")),
        '{}:{}'.format(
          m.group("intervall_minutes"),
          m.group("intervall_seconds"))
      ]
      log('Start {} at {}:{} with intervall {}:{}'.format(path, m.group("starttime_minutes"), m.group("starttime_seconds"), m.group("intervall_minutes"),  m.group("intervall_seconds")))
      subprocess.call(cmd)
      exit(0)

subprocess.call(["/usr/bin/fbi", "-T", "1", "-noverbose",  "/var/share/gruselpi/no_video.png"])
exit(1)
