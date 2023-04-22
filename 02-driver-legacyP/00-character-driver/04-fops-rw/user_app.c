/**
 * \file user_app.c
 * \author Nguyen Trong Phong
 * \date 4/20/2023
 * \details Program in user space for interactive to LED driver
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "errmacros.h"

#define CDEV_PATH "/dev/led_device"

char write_buf[1024];
char read_buf[1024];

/* Hàm kiểm tra entry point open của LED Driver */
int open_leddev()
{
    int fd = open(CDEV_PATH, O_RDWR);
    if (fd < 0)
    {
        FILE_OPEN_ERROR(fd);
    }

    return fd;
}

/* Hàm kiểm tra entry point close của LED Driver */
void close_leddev(int fd)
{
    close(fd);
    FILE_CLOSE_ERROR(errno);
}
int main(int argc, char const *argv[])
{
    char option = 'q';
    int fd = -1;

    printf("Select below options:\n");
    printf("\to (to open a device node)\n");
    printf("\tc (to close the device node)\n");
    printf("\tw (to write the device node)\n");
    printf("\tr (to read the device node)\n");
    printf("\tq (to quit the application)\n");
    while (1)
    {
        printf("Enter your option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case 'o':
            if (fd < 0)
                fd = open_leddev();
            else
                printf("%s has already opened\n", CDEV_PATH);
            break;
        case 'c':
            if (fd > -1)
                close_leddev(fd);
            else
                printf("%s has not opened yet! Can not close\n", CDEV_PATH);
            fd = -1;
            break;
        case 'q':
            if (fd > -1)
                close_leddev(fd);
            printf("Quit the application. Good bye!\n");
            return 0;
        case 'w':
            printf("Enter the string to write into driver: ");
            scanf("  %[^\t\n]s", write_buf);
            printf("Data Writing ... ");
            write(fd, write_buf, strlen(write_buf) + 1);
            printf("Done!\n\n\n");
            break;
        case 'r':
            printf("Data Reading ... ");
            read(fd, read_buf, 1024);
            printf("Done!\n");
            printf("Data: %s\n\n\n", read_buf);
            break;
        default:
            printf("invalid option %c\n", option);
            break;
        }
    };

    return 0;
}
