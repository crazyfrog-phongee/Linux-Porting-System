obj-m = led.o

CROSS = /home/phongee_hust/Working-Space/Beagle-Bone-Black/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KERNEL = /home/phongee_hust/Working-Space/Beagle-Bone-Black/kernelbuildscripts/KERNEL
KDIR = /lib/modules/`uname -r`/build

EXTRA_CFLAGS = -Wall

UNAME := $(shell uname -m)

all:
	$(Info checking if custom header is needed)
ifeq ($(UNAME), x86_64)
	make -C $(KDIR) M=`pwd` modules
else
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) M=$(PWD) modules
endif

clean:
	make -C $(KERNEL) M=$(PWD) clean