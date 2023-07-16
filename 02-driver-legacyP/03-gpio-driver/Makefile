obj-m = led.o

TITLE_COLOR = \033[33m
NO_COLOR = \033[0m
CROSS = /home/phongee_hust/Working-Space/Beagle-Bone-Black/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KERNEL = /home/phongee_hust/Working-Space/Beagle-Bone-Black/kernelbuildscripts/KERNEL
KDIR = /lib/modules/`uname -r`/build

EXTRA_CFLAGS = -Wall
# UNAME := $(shell uname -m)
UNAME := arm
# CC := arm-linux-gnueabihf-gcc

# when excuting make, compile all exe's
all: clean
	$(Info checking if custom header is needed)
	@echo "$(TITLE_COLOR)\n***** COMPILING user_app *****$(NO_COLOR)"
	arm-linux-gnueabihf-gcc -o user_app $(EXTRA_CFLAGS) user_app.c
ifeq ($(UNAME), x86_64)
	make -C $(KDIR) M=`pwd` modules
else
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) M=$(PWD) modules
endif

# do not look for files called clean, clean-all or this will be always a target
.PHONY: clean
clean:
	make -C $(KERNEL) M=$(PWD) clean
	rm -rf user_app

leak: all
	@echo "$(TITLE_COLOR)\n***** LEAK CHECK user_app *****$(NO_COLOR)"
	valgrind --leak-check=full -v --track-origins=yes --show-leak-kinds=all ./user_app

run:
	@echo "$(TITLE_COLOR)\n***** RUNNING user_app *****$(NO_COLOR)"
	./user_app