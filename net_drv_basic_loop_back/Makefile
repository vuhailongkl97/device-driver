obj-m:= main.o
KDIR := /lib/modules/$(shell uname -r)/build 

ARCH :=
CROSS_COMPILE:=
all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean 
