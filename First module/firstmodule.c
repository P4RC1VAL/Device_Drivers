#include <linux/init.h>            
#include <linux/module.h>        
#include <linux/kernel.h> 
#include <linux/printk.h>          
 
MODULE_LICENSE("GPL");             
MODULE_AUTHOR("P4RC1VAL");     
MODULE_DESCRIPTION("A first Linux module");  
MODULE_VERSION("0.1");              

 //initializing module
static int __init simple_init(void){
   pr_info("Module had been included in the system\n");
   return 0;
}
 
//cleanup module
static void __exit simple_exit(void){
   pr_info("Module had been disconnected.\n");
}
 
module_init(simple_init);
module_exit(simple_exit);
