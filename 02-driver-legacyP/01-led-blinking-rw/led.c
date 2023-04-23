/**
 * \file led.c
 * \author Nguyen Trong Phong
 * \date 4/18/2023
 * \details LED character driver for led character device
 */

#include <linux/module.h>  /* Need for some macros such as module_init, module_exit */
#include <linux/fs.h>      /* Need for functions such as allocation/release device number */
#include <linux/device.h>  /* Need for functions to creating device file; structure file_operations */
#include <linux/cdev.h>    /* Need for functions such as cdev_init, cdev_add */
#include <linux/slab.h>    /* Need for functions such as kmalloc, kfree */
#include <linux/io.h>      /* Need for functions such as ioremap, iounmap */
#include <linux/uaccess.h> /* Need for functions such as copy_to_user/copy_from_user */

#include "led.h"

#define DRIVER_AUTHOR "NTPhong-Penguin-EmbeddedLinux"
#define DRIVER_DESC "LED Kernel Module"
#define DRIVER_VERS "1.0"

#define NPAGES 1

// struct registers
// {
//     int gpio_oe = GPIO_OE_OFFSET;
//     int gpio_cleardataout = GPIO_CLEARDATAOUT_OFFSET;
//     int gpio_setdataout = GPIO_SETDATAOUT_OFFSET;
// };

struct gpios
{
    int numb;
    int status;
    int direction;
    // struct registers reg;
};

struct gpio_banks
{
    struct gpios gpios[32];
    uint32_t __iomem *base_addr;
};

struct _vchar_drv
{
    int size;
    char *kmalloc_ptr;
    dev_t dev_num;
    struct class *dev_class;
    struct cdev m_cdev;
    struct gpio_banks banks[4];
} led_drv;

uint32_t __iomem *base_addr_led_red;
// uint32_t __iomem *base_addr_led_green;
uint32_t __iomem *base_addr;

/****************************** Device specific - START *****************************/
static int __gpio_init(struct gpio_banks *bank, int number);
static int __gpio_exit(void);
static void __control_led(struct gpio_banks *bank, int number, int direct, int value);

/* Hàm khởi tạo thiết bị */
static int __gpio_init(struct gpio_banks *bank, int number)
{
    bank->gpios[number].status = GPIO_SET_OFF;
    bank->gpios[number].direction = GPIO_SET_INPUT;
    bank->base_addr = ioremap(GPIO_0_ADDR_BASE, GPIO_0_ADDR_SIZE);
    if (!bank->base_addr)
        return -ENOMEM;

    // *(led_drv.banks[GPIO_BANK_0].base_addr + GPIO_OE_OFFSET / 4) &= ~(1 << LED_RED);
    return 0;
}
/* Hàm giải phóng thiết bị */
static int __gpio_exit(void)
{
    // iounmap(base_addr_led_red);
    return 0;
}
/* Hàm đọc từ các thanh ghi dữ liệu của thiết bị */

/* Hàm ghi vào các thanh ghi dữ liệu của thiết bị */
static void __control_led(struct gpio_banks *bank, int number, int direct, int value)
{
    // unsigned long temp = ioread32(base_addr_led_red + GPIO_SETDATAOUT_OFFSET);

    // pr_info("Value of temp: %ld\n", temp);

    if (direct == GPIO_SET_OUTPUT)
    {
        printk("%s %d", __func__, __LINE__);
        *(bank->base_addr + GPIO_OE_OFFSET / 4) &= ~(1 << number);
        printk("%s %d", __func__, __LINE__);
    }

    printk("%s %d %d", __func__, __LINE__, value);

    if (value == GPIO_SET_ON)
    {
        printk("%s %d", __func__, __LINE__);
        *(bank->base_addr + GPIO_SETDATAOUT_OFFSET / 4) |= (1 << number);
        pr_info("Set GPIO Output HIGH\n");
        printk("%s %d", __func__, __LINE__);
    }
    else // GPIO_SET_OFF
    {
        printk("%s %d", __func__, __LINE__);
    }
    // if (value)
    // {
    //     *(base_addr_led_red + GPIO_SETDATAOUT_OFFSET / 4) |= (1 << LED_RED);
    //     pr_info("Set GPIO Output HIGH\n");
    // }
    // else
    // {
    //     *(base_addr_led_red + GPIO_CLEARDATAOUT_OFFSET / 4) |= (1 << LED_RED);
    //     pr_info("Set GPIO Output LOW\n");
    // }
}
/* Hàm đọc từ các thanh ghi trạng thái của thiết bị */

/* Hàm ghi vào các thanh ghi điều khiển của thiết bị */

/* Hàm xử lý tín hiệu ngắt gửi từ thiết bị */

/******************************** OS specific - START *******************************/

static int __init led_init(void);
static void __exit led_exit(void);
static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset);
static ssize_t m_write(struct file *filp, const char *user_buf, size_t size, loff_t *offset);

static struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .open = m_open,
        .release = m_release,
        .read = m_read,
        .write = m_write,
};

/* Các hàm entry points */

/* This function will be called when we open the device file */
static int m_open(struct inode *inode, struct file *file)
{
    pr_info("System call open() called...!!!\n");
    return 0;
}

/* This function will be called when we close the Device file */
static int m_release(struct inode *inode, struct file *file)
{
    pr_info("System call close() called...!!!\n");
    return 0;
}

/* This function will be called when we read the Device file */
static ssize_t m_read(struct file *filp, char __user *user_buffer, size_t size, loff_t *offset)
{
    pr_info("System call read() called...!!!\n");
    pr_info("[In function m_read]Before: Value of variables: offset = %d, led_drv.size = %d, size = %d\n", *((int *)offset), led_drv.size, (int)size);

    pr_info("[In function m_read]After: Value of variables: offset = %d, led_drv.size = %d, size = %d\n", *((int *)offset), led_drv.size, (int)size);
    return 0;
}

/* This function will be called when we write the Device file */
static ssize_t m_write(struct file *filp, const char __user *user_buffer, size_t size, loff_t *offset)
{
    long gpio_num;
    int index;
    int number;

    pr_info("System call write() called...!!!\n");
    // pr_info("[In function m_write]Before: Value of variables: offset = %d, led_drv.size = %d, size = %d\n", *((int *)offset), led_drv.size, (int)size);

    /* Copy from user buffer to mapped area */
    memset(led_drv.kmalloc_ptr, 0, 1024);
    if (copy_from_user(led_drv.kmalloc_ptr, user_buffer, size) != 0)
        return -EFAULT;

    if (kstrtol(led_drv.kmalloc_ptr, 10, &gpio_num))
    {
        pr_err("On error\n");
        return -1;
    }

    index = gpio_num / 32;
    number = gpio_num % 32;
    switch (index)
    {
    case GPIO_BANK_0:
        __gpio_init(&led_drv.banks[GPIO_BANK_0], number);
        printk("%s %d", __func__, __LINE__);
        __control_led(&led_drv.banks[GPIO_BANK_0], number, GPIO_SET_OUTPUT, GPIO_SET_ON);
        printk("%s %d", __func__, __LINE__);
        break;

    case GPIO_BANK_1:
        break;
    case GPIO_BANK_2:
        break;
    case GPIO_BANK_3:
        break;

    default:
        break;
    }
    led_drv.banks[gpio_num / 32].gpios.numb = gpio_num % 32;

    // if (0 == strcmp(led_drv.kmalloc_ptr, "0"))
    // {
    //     __set_output_led(0);
    // }
    // else if (0 == strcmp(led_drv.kmalloc_ptr, "1"))
    // {
    //     __set_output_led(1);
    // }
    // else
    // {
    //     pr_info("Unknown command\n");
    // }

    pr_info("%s %d: Data from usr: %s %ld", __func__, __LINE__, led_drv.kmalloc_ptr, gpio_num);
    pr_info("%s %d: Bank = %ld, Gpio_num_bank = %d\n", __func__, __LINE__, gpio_num / 32, led_drv.banks[gpio_num / 32].gpios.numb);
    // pr_info("[In function m_write]After: Value of variables: led_drv.size = %d, size = %d\n", led_drv.size, (int)size);
    return size;
}

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

    /* 3. Cấp phát bộ nhớ cho các cấu trúc dữ liệu của driver và khởi tạo */
    if ((led_drv.kmalloc_ptr = kmalloc(1024, GFP_KERNEL)) == 0)
    {
        pr_err("Cannot allocate memory in kernel\n");
        goto rm_device;
    }

    /* 4. Khởi tạo thiết bị vật lý */
    // __gpio_init();

    /* 5. Đăng ký các entry point với kernel */
    /* 5.1 Creating cdev structure */
    cdev_init(&led_drv.m_cdev, &fops);

    /* 5.2 Adding character device to the system */
    ret = cdev_add(&led_drv.m_cdev, led_drv.dev_num, 1);
    if (ret < 0)
    {
        pr_err("Cannot add the device to the system\n");
        goto rm_device;
    }

    /* Đăng ký hàm xử lý ngắt */

    pr_info("Major = %d Minor = %d\n", MAJOR(led_drv.dev_num), MINOR(led_drv.dev_num));
    printk(KERN_INFO "Hello World from Kernel Module\n");
    return 0; /* A non-zero return means init_module failed; module can't be loaded */

rm_device:
    device_destroy(led_drv.dev_class, led_drv.dev_num);
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
    cdev_del(&led_drv.m_cdev);
    /* Giải phóng thiết bị vật lý */
    __gpio_exit();
    /* Giải phóng bộ nhớ đã cấp phát cho cấu trúc dữ liệu của driver */
    kfree(led_drv.kmalloc_ptr);
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
