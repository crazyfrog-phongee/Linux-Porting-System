#include <linux/module.h>   /* Needed for all modules */
#include <linux/kernel.h>   /* Neeeded for KERN_INFO */
#include <linux/io.h>

#include "led.h"

#define DRIVER_AUTHOR "NTPhong-Penguin-EmbeddedLinux"
#define DRIVER_DESC   "Blink LED Kernel Module"
#define DRIVER_VERS   "1.0"

uint32_t __iomem *base_addr_led_red;
uint32_t __iomem *base_addr_led_green;

static int __init led_init(void)
{
    printk(KERN_INFO "Starting from LED Kernel Module\n");
    base_addr_led_red = ioremap(GPIO_0_ADDR_BASE, GPIO_0_ADDR_SIZE);
    if (!base_addr_led_red)
        return -ENOMEM;
    base_addr_led_green = ioremap(GPIO_1_ADDR_BASE, GPIO_1_ADDR_SIZE);
    if (!base_addr_led_green)
        return -ENOMEM;
    
    *(base_addr_led_red + GPIO_OE_OFFSET / 4) &= ~LED_RED;
    *(base_addr_led_red + GPIO_SETDATAOUT_OFFSET / 4) |= LED_RED;

    *(base_addr_led_green + GPIO_OE_OFFSET / 4) &= ~LED_GREEN;
    *(base_addr_led_green + GPIO_SETDATAOUT_OFFSET / 4) |= LED_GREEN;

    pr_info("Initialize LED Kernel Module successfully!\n");
    return 0; /* A non-zero return means init_module failed; module can't be loaded */
}

static void __exit led_exit(void)
{
    *(base_addr_led_red + GPIO_CLEARDATAOUT_OFFSET / 4) |= LED_RED;
    *(base_addr_led_green + GPIO_CLEARDATAOUT_OFFSET / 4) |= LED_GREEN;

    iounmap(base_addr_led_red);
    iounmap(base_addr_led_green);

    pr_info("Finished LED Kernel Module successfully!\n");
    printk(KERN_INFO "Goodbye\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);