/**
 * \file led.c
 * \author Nguyen Trong Phong
 * \date 4/18/2023
 * \details LED character driver for led character device
 */

#include <linux/module.h> /* Need for some macros such as module_init, module_exit */
#include <linux/fs.h>  /* Need for functions such as allocation/release device number */

#define DRIVER_AUTHOR "NTPhong-Penguin-EmbeddedLinux"
#define DRIVER_DESC   "LED Kernel Module"
#define DRIVER_VERS   "1.0"

struct _vchar_drv {
    dev_t dev_num; /* Storing device number */
} led_drv;

/******************************** OS specific - START *******************************/

static int  __init led_init(void);
static void __exit led_exit(void);

/* Driver Constructor */
static int __init led_init(void)
{
    int ret;
    /* 1. Allocating device number */
    /* 1.1 Static allocating device number (cat /proc/devices) */
    // led_drv.dev_num = MKDEV(235, 0);
    // ret = register_chrdev_region(led_drv.dev_num, 1, "led_device");
    // if (ret < 0)
    // {
    //     pr_err("Failed to register device number statically\n");
    //     goto rm_device_num;
    // }

    /* 1.2 Dynamic allocating device number */
    ret = alloc_chrdev_region(&led_drv.dev_num, 0, 1, "led_device");
    if (ret < 0) 
    {
        pr_err("Failed to register device number dynamically\n");
        goto failed_register_devivce_num;
    }

    /* Create device file */

    /* Cấp phát bộ nhớ cho các cấu trúc dữ liệu của driver và khởi tạo */

    /* Khởi tạo thiết bị vật lý */

    /* Đăng ký các entry point với kernel */

    /* Đăng ký hàm xử lý ngắt */

    pr_info("Major = %d Minor = %d\n", MAJOR(led_drv.dev_num), MINOR(led_drv.dev_num));
    printk(KERN_INFO "Hello World from Kernel Module\n");
    return 0; /* A non-zero return means init_module failed; module can't be loaded */

failed_register_devivce_num:
    return ret;
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
    unregister_chrdev_region(led_drv.dev_num, 1);

    printk(KERN_INFO "Goodbye\n");
}
/******************************** OS specific - END *******************************/

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);
