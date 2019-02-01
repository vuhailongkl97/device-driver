#!/bin/bash

echo "0 stop deamon"
echo "1 start deamon"
echo "2 getlog deamon"
echo "3 set default config deamon"
echo "4 get status watchdog "

read -p "MODE " MODE

if [ $MODE -eq 0 ] 
then 
	sudo service watchdog stop
elif [ $MODE -eq 1 ] 
then 
	sudo service watchdog start
elif [ $MODE -eq 2 ]
then 
	tail -n 30 /var/log/syslog |  less
elif [ $MODE -eq 3 ]
then 
	sudo vi /etc/default/watchdog
elif [ $MODE -eq 4 ] 
then 
	systemctl status watchdog.service
else
	echo "argument incorrect"
fi


