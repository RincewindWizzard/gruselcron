#!/bin/bash
onion=`cat /var/lib/tor/hidden_service/hostname`
torify ssh pi@6ngxr2uabq3i4ilu.onion -i /home/pi/.ssh/id_rsa "echo $onion > /home/pi/clients/$onion"
