obj-m := main.o

KDIR ?= /lib/modules/$(shell uname -r)/build

all default: modules

modules clean:
	make -C $(KDIR) M=$(PWD) $@
