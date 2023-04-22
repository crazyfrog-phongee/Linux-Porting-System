/**
 * \file led.c
 * \author Nguyen Trong Phong
 * \date 4/18/2023
 * \details LED character driver for led character device
 */

#include <linux/module.h> /* Need for some macros such as module_init, module_exit */
#include <linux/fs.h>  /* Need for functions such as allocation/release device number */
#include <linux/device.h> /* Need for functions to creating device file */

#define DRIVER_AUTHOR "NTPhong-Penguin-EmbeddedLinux"
#define DRIVER_DESC   "LED Kernel Module"
#define DRIVER_VERS   "1.0"

struct _vchar_drv {
    dev_t dev_num;
    struct class *dev_class;
} led_drv;

/****************************** Device specific - START *****************************/

/* Hàm khởi tạo thiết bị */

/* Hàm giải phóng thiết bị */

/* Hàm đọc từ các thanh ghi dữ liệu của thiết bị */

/* Hàm ghi vào các thanh ghi dữ liệu của thiết bị */

/* Hàm đọc từ các thanh ghi trạng thái của thiết bị */

/* Hàm ghi vào các thanh ghi điều khiển của thiết bị */

/* Hàm xử lý tín hiệu ngắt gửi từ thiết bị */

/******************************** OS specific - START *******************************/

static int      __init led_init(void);
static void     __exit led_exit(void);

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
    /* 2. Create device file */
    /* 2.1 Creating struct class: device class (/sys/class) */

    /* Chức năng: Tạo ra một lớp các thiết bị có tên là [name] trong
    *            thư mục /sys/class. Lớp này chứa liên kết tới thông
    *            tin của các thiết bị cùng loại.
    *  Tham số truyền vào:
    *   *owner [I]: con trỏ trỏ tới module sở hữu lớp thiết bị này
    *   *name  [I]: tên của lớp các thiết bị
    *  Return:
    *    Nếu thành công, thư mục có tên [name] được tạo ra trong
    *    /sys/class. Hàm trả về một con trỏ trỏ tới biến cấu trúc class.
    *    Nếu thất bại, trả về NULL
    */
    if ((led_drv.dev_class = class_create(THIS_MODULE, "class_led_device")) == NULL)
    {
        pr_err("Cannot create the struct class for my device\n");
        goto rm_device_num;
    }

    /* 2.2 Creating device (/dev) */

    /*
    * Chức năng: Tao ra các thông tin của một thiết bị cụ thể trên class
    *            Khi có thông tin này, udev sẽ tạo ra một device file
    *            tương ứng trong /dev
    * Tham số truyền vào:
    *    *cls    [I]: con trỏ trỏ tới lớp các thiết bị. Con trỏ này là kết
    *                 quả của việc gọi hàm class_create
    *    *parent [I]: con trỏ trỏ tới thiết bị cha của thiết bị này. Nếu
    *                 thiết bị không có cha, ta truyền vào là NULL
    *    devt    [I]: device number của thiết bị.
    *    *drvdata[I]: dữ liệu bổ sung. Nếu không có, ta truyền vào là NULL.
    *    *name   [I]: tên của thiết bị. udev sẽ tạo ra device file với tên
    *                 này trong thư mục /dev
    */
    if ((device_create(led_drv.dev_class, NULL, led_drv.dev_num, NULL, "led_device")) == NULL)
    {
        pr_err("Cannot create my device\n");
        goto rm_class;
    }

    /* Cấp phát bộ nhớ cho các cấu trúc dữ liệu của driver và khởi tạo */

    /* Khởi tạo thiết bị vật lý */

    /* Đăng ký các entry point với kernel */

    /* Đăng ký hàm xử lý ngắt */

    pr_info("Major = %d Minor = %d\n", MAJOR(led_drv.dev_num), MINOR(led_drv.dev_num));
    printk(KERN_INFO "Hello World from Kernel Module\n");
    return 0; /* A non-zero return means init_module failed; module can't be loaded */

rm_class:
    class_destroy(led_drv.dev_class);
rm_device_num:
    unregister_chrdev_region(led_drv.dev_num, 1);
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
    device_destroy(led_drv.dev_class, led_drv.dev_num);
    class_destroy(led_drv.dev_class);

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
