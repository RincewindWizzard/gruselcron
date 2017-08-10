all:
	cd src; make

sshkey:
	mkdir -p ~/.ssh/
	cp config ~/.ssh/config
	cp id_rsa ~/.ssh/id_rsa

install: all
	mkdir -p /var/share/gruselpi
	cp ./bin/gruselcron /usr/bin/gruselcron
	cp ./bin/showtime /usr/bin/showtime
	cp ./findvideo.py /usr/bin/findvideo.py
	cp ./res/usb_stick_erkannt.png /var/share/gruselpi/usb_stick_erkannt.png
	cp ./res/too_much_videos.png /var/share/gruselpi/too_much_videos.png
	cp ./res/no_video.png /var/share/gruselpi/no_video.png
	cp ./gruselboot.sh /var/share/gruselpi/gruselboot.sh

uninstall:
	rm -f /etc/init/gruselcron.conf
	rm -f /usr/bin/gruselcron
	rm -f /var/log/gruselcron.log
	rm -f /usr/bin/showtime
	rm -f /usr/bin/findvideo.py
	rm -rf /var/share/gruselpi


update:
	sudo make uninstall
	git pull origin master
	sudo make install


clone: config id_rsa sshkey
	ssh server echo "Succesful added remote"
	git clone git@server:dfl/gruselpi.git
	cd ./gruselpi; make update

push:
	git add -A . && git commit -m "auto push" && git push origin master && ssh gruselpi -l pi "cd /home/pi/gruselpi; make update;"
