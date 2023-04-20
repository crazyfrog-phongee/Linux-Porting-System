obj-m = led.o

CROSS = /home/phongee_hust/Working-Space/Beagle-Bone-Black/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KERNEL = /home/phongee_hust/Working-Space/Beagle-Bone-Black/kernelbuildscripts/KERNEL

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) M=$(PWD) modules

clean:
	make -C $(KERNEL) M=$(PWD) clean