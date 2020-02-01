description :
	test spi driver 

how to test ?

	1. make 
	2. ./spidev_test
	
	3. if result is a array which look : 
spi mode: 0
bits per word: 8
max speed: 500000 Hz (500 KHz)

FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF 

>> spi driver has received data yet ? 

to test receiving data . you connect P9_18 (miso) > P9_21 (mosi) 

result will be

spi mode: 0
bits per word: 8
max speed: 500000 Hz (500 KHz)

FF FF FF FF FF FF 
40 00 00 00 00 95 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
DE AD BE EF BA AD 
F0 0D 
