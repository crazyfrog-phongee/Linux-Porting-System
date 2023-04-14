.PHONY : all clean

EXTRA_CFLAGS = -Wall
obj-m = userspace.o

CC := arm-linux-gnueabihf-gcc
all:
	$(CC) -o hello_userspace userspace.c

clean:
	rm -rf hello_userspace