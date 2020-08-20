# LinuxKit:
obj-m += mtd.o
mtd-objs := task_state.o mtd_main.o

KVER=$(shell basename /usr/src/linux-headers-*)
all:
	make -C /usr/src/$(KVER) M=$(PWD) modules
clean:
	make -C /usr/src/$(KVER) M=$(PWD) clean


# Ubuntu:
# obj-m += mtd.o
# mtd-objs := task_state.o mtd_main.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

ubuntu:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean_ubuntu:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

