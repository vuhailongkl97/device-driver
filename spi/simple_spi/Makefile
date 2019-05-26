obj-m := main.o

KDIR ?= /lib/modules/$(shell uname -r)/build

all default: modules

clean modules:
	make -C $(KDIR) M=$(PWD) $@
