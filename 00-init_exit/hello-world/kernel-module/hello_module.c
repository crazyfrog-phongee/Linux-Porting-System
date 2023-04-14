#include <linux/module.h>   /* Needed for all modules */
#include <linux/kernel.h>   /* Neeeded for KERN_INFO */

#define DRIVER_AUTHOR "NTPhong-Penguin-EmbeddedLinux"
#define DRIVER_DESC   "Hello World Kernel Module"
#define DRIVER_VERS   "1.0"

static int __init hello_world_init(void)
{
    printk(KERN_INFO "Hello World from Kernel Module\n");
    return 0; /* A non-zero return means init_module failed; module can't be loaded */
}

static void __exit hello_world_exit(void)
{
    printk(KERN_INFO "Goodbye\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);