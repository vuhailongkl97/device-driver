# vuhailong
# 01/02/2019

how to run wdt with wdt deamon 

0. stop watchdog driver using command ( permition as root) : 
	echo 'V' > /dev/watchdog

1. insmod wdt driver 
	sudo insmod main.ko

2. run wdt_deamon for control watchdog  over /dev/my_watchdog ( After config /etc/watchdog.conf )
	config corresponding  "test config"  below

3. check log with bash scrip ( ./deamon_control.sh ) 

4. To stop using command : 
	./deamon_control.sh >> choose 0 option 
	


note :  	
	need stop waitdog driver build in before using own driver because it can conflict

// TEST CONFIG 
	config   in /etc/watchdog.conf
	add : 
			
		watchdog-device  = /dev/my_watchdog # own device file  

		ping  = 192.168.7.1    # ip static config over usb0  of beaglebone 
	        ping-count = 3         #  check ping 3 times to "ping" 	

		file  = /var/log/syslog   
		change = 100            # old of "file"  if more than 100 > check fail >> watchdog reset board 

Refer to get more information about watchdog driver : http://www.sat.dundee.ac.uk/~psc/watchdog/Linux-Watchdog.html

		
		


