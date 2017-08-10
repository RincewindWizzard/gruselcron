#!/bin/bash
# pump up the volume
amixer cset numid=1 400

# copy new data from usb
if mountpoint /media/usb
then
	/usr/bin/fbi -T 1 -noverbose /var/share/gruselpi/usb_stick_erkannt.png > /dev/null
	rsync -av --delete /media/usb/ /mnt/
	cp /var/log/upstart/gruselcron.log /media/usb/
	killall fbi
	umount /media/usb
fi
rm /mnt/gruselcron.log

filecount=`ls -1 /mnt/ | wc -l`
if [ -f "/mnt/standbild.jpg" ]
then
	filecount=`expr $filecount - 1`
fi
echo $filecount > /tmp/fc
if (( $filecount > 1 ))
then
	/usr/bin/fbi -T 1 -noverbose  /var/share/gruselpi/too_much_videos.png > /dev/null
fi	
touch /var/log/gruselcron.log
(( $filecount == 1 )) && [ -f "/mnt/standbild.jpg" ] && /usr/bin/fbi -T 1 -noverbose /mnt/standbild.jpg > /dev/null
chmod -R ogu+rwx /mnt/
findvideo.py
