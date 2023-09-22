#include <linux/init.h>          
#include <linux/module.h>          
#include <linux/kernel.h> 
#include <linux/kdev_t.h>
#include <linux/fs.h>  
#include <asm/uaccess.h>        
 
MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Maximus");      
MODULE_DESCRIPTION("A simple Linux symbol driver");  
MODULE_VERSION("1.0");

#define DRV_NAME "sym_chrdev"
dev_t Major;
int Device_Open = 0;
int signal_cnt = 0;
char msg = 'Hello!';

int sym_open(struct inode *inode, struct file *file)
{
	signal_cnt = 0;
	if (Device_Open)
		return -EBUSY;
	
	Device_Open++;
	try_module_get(THIS_MODULE);
	
	return 0;
}

ssize_t sym_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	
	memcpy(msg, &signal_cnt, sizeof(int));
	
	if(length > 5)
		length = 5;
	
	copy_to_user(buffer,msg,length);
	
	return length;

		
}

int sym_release(struct inode *inode, struct file *file)
{
	Device_Open--;
	module_put(THIS_MODULE);
	
	return 0;
}

struct file_operations file_ops = {
	.read = sym_read,
	//.write = sym_write,
	.open = sym_open,
	.release = sym_release
};


int init_module(void) 
{
	printk(KERN_INFO "Hello world !.\n");
	
	Major = register_chrdev(0, DRV_NAME, &file_ops);
	if (Major < 0)
	{
		printk(KERN_ALERT "Error while registering chrdev with %d\n", Major);
		return Major;
	}
	
	printk(KERN_INFO "symbol chrdev has got major number %d\n", Major);
	printk(KERN_INFO "use mknod /dev/%s c %d 0\n", DRV_NAME, Major);

	return 0;
}

void cleanup_module(void) 
{
	unregister_chrdev(Major, DRV_NAME);
	printk(KERN_ALERT "Symbol driver module disengaged!\n");
}
