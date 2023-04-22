/**
 * \file led.c
 * \author Nguyen Trong Phong
 * \date 4/18/2023
 * \details LED character driver for led character device
 */

#include <linux/module.h> /* Define some macros: module_init, module_exit */

#define DRIVER_AUTHOR "NTPhong-Penguin-EmbeddedLinux"
#define DRIVER_DESC   "LED Kernel Module"
#define DRIVER_VERS   "1.0"

/****************************** Device specific - START *****************************/

/* Hàm khởi tạo thiết bị */

/* Hàm giải phóng thiết bị */

/* Hàm đọc từ các thanh ghi dữ liệu của thiết bị */

/* Hàm ghi vào các thanh ghi dữ liệu của thiết bị */

/* Hàm đọc từ các thanh ghi trạng thái của thiết bị */

/* Hàm ghi vào các thanh ghi điều khiển của thiết bị */

/* Hàm xử lý tín hiệu ngắt gửi từ thiết bị */

/******************************** OS specific - START *******************************/
static int __init led_init(void);
static void __exit led_exit(void);

/* Driver Constructor */
static int __init led_init(void)
{
    /* Allocating device number */

    /* Create device file */

    /* Cấp phát bộ nhớ cho các cấu trúc dữ liệu của driver và khởi tạo */

    /* Khởi tạo thiết bị vật lý */

    /* Đăng ký các entry point với kernel */

    /* Đăng ký hàm xử lý ngắt */

    printk(KERN_INFO "Hello World from Kernel Module\n");
    return 0; /* A non-zero return means init_module failed; module can't be loaded */
}

/* Driver Destructor */
static void __exit led_exit(void)
{
    /* Hủy đăng ký xử lý ngắt */

    /* Hủy đăng ký entry point với kernel */

    /* Giải phóng thiết bị vật lý */

    /* Giải phóng bộ nhớ đã cấp phát cho cấu trúc dữ liệu của driver */

    /* Xóa bỏ device file */

    /* Giải phóng device number */

    printk(KERN_INFO "Goodbye\n");
}
/********************************* OS specific - END ********************************/

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);
