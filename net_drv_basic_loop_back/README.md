basic network driver : copy loopback driver as "lo" in (ifconfig)

USE new loopback driver :
	after add new driver 
	we can't using socket over virtual network  ip

HOW TO USE:
	step 1: insert module and run server 
		sudo chmod +x my_loopback_setup.sh
		sudo chmod +x client_and_clean_module.sh
		./my_loopback_setup.sh

	step 2: client test
		open new terminal and run 
		./client_and_clean_module.sh
