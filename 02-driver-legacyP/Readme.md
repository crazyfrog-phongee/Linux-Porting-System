# TOPIC: Viết một chương trình blink LED trên userspace
## DESCRIPTION:
LED1: P8.16 <=> GPIO46 (GPIO_NUM_46) <=> GPIO1[14]
LED2: P9.13 <=> GPIO31 (GPIO_NUM_31) <=> GPIO0[31]
Yêu cầu: Không được sử dụng GPIO subsystem (/sys/class/gpio)
**Note:** Các thư mục nằm trong /sys được gọi là sysfs
Major number + Minor number = Device number