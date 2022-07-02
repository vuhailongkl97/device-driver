description :
	test spi driver 

how to test ?

	0. config pin via supported commands or device tree overlay
	1. make 
	2. ./spidev_test
	
	3. if result is a array which look : 
0. 
# For SPI1, /dev/spidev1.#  
#
config-pin p9_17 spi_cs
config-pin p9_18 spi
config-pin p9_21 spi
config-pin p9_22 spi_sclk  
 
# For SPI0, /dev/spidev2.#
#
config-pin p9_28 spi_cs
config-pin p9_29 spi
config-pin p9_30 spi
config-pin p9_31 spi_sclk  


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


