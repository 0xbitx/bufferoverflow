obj-m := hooker.o

KDIR=/home/korkeep/HackRPi/linux/
PWD=$(shell pwd)
TOOLCHAIN=arm-linux-gnueabihf-
TARGET=arm

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(TARGET) CROSS_COMPILE=$(TOOLCHAIN) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

