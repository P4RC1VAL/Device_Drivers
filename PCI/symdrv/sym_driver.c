#include <linux/init.h>          
#include <linux/module.h>          
#include <linux/kernel.h> 
#include <linux/kdev_t.h>
#include <linux/fs.h>  
#include <asm/uaccess.h>        
 
MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Maximus");      
MODULE_DESCRIPTION("A PCI-device symbol driver");  
MODULE_VERSION("1.0");

#define DRV_NAME "PCI_chrdev"
#define MY_IOCTL_CMD_READ_DATA _IOR(77, 1, char*)
#define ETH_ALEN 6
#define BUF_LEN 1024
unsigned char mac_addr[ETH_ALEN];
dev_t Major;
int Device_Open = 0;

int device_open(struct inode *inode, struct file *file)
{

	if (Device_Open)
		return -EBUSY;
	
	Device_Open++;
	try_module_get(THIS_MODULE);
	
	return 0;
}

ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	
	
	if(length > 7)
		length = 7;
	
	copy_to_user(buffer,mac_addr,length);
	printk(KERN_INFO "symbol chrdev has sent message: %d\n", mac_addr);
	
	return length;

		
}

int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;
	module_put(THIS_MODULE);
	
	return 0;
}


static long my_ioctl(struct file *filep, unsigned int cmd, unsigned long arg) {
	printk(KERN_INFO "*** inside ioctl*** \n");
	int data_size = 0;
	printk(KERN_INFO "IOCTL MAC address: %pM\n", mac_addr); 
        printk(KERN_INFO "IOCTL cmd: %d\n", cmd); 
    
    	switch (cmd) {
        	case MY_IOCTL_CMD_READ_DATA:
            	// copy data from kernel space to user space
            		data_size = strlen(mac_addr) + 1;
            		if (copy_to_user((char *)arg, mac_addr, data_size)) {
                		return -EFAULT;
            		}
			break;
        	default:
            		return -ENOTTY; // unsupported command
	}
	return 0;
}

static struct file_operations fops = {
	.read = device_read,
	.unlocked_ioctl = my_ioctl,
	.open = device_open,
	.release = device_release
};



int init_module(void) 
{
	printk(KERN_INFO "Hello!.\n");
	
	Major =register_chrdev(0, DRV_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "Registreing char device failed with %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "I was assigned major number %d. To talk to \n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "mknod /dev/%s c %d 0'.\n", DRV_NAME, Major);

	return 0;
}

void cleanup_module(void) 
{
	unregister_chrdev(Major, DRV_NAME);
	printk(KERN_ALERT "Symbol driver module disengaged!\n");
}
