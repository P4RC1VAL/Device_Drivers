#include <linux/module.h>
#include <linux/kernel.h>
#define DEVICE_NAME "100"
MODULE_LICENSE("GPL");

int init_module(void){
	Major =register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "Registreing char device failed with %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "I was assigned major number %d. To talk to \n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	return SUCCESS;
}

void cleanup_module(void){
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_ALERT "Cleanup_module OK\n");
}