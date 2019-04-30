obj-m := mpu_driver.o
mpu_driver-objs := main.o mpu6050.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc test_mpu.c -o t -lm -pthread
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
	rm -f *.dtbo
	rm -f dt
	rm -f t
