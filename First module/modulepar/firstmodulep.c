#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
MODULE_LICENSE("GPL");

static char *whom = "Admin";
module_param(whom, charp, 0);
static int howmany = 1;
module_param(howmany, int, 0);         // Передается пара параметров - сколько рaз и  кому передается 
static int __init hello_init(void) {
    int i;
    for (i = 0; i < howmany; i++)  	
      printk(KERN_ALERT "(%d) Module had been included, %s\n", i, whom);
    return 0;
}
static void __exit hello_exit(void) {
    printk(KERN_ALERT "Module had been disconnected, %s\n", whom);
}
module_init(hello_init);
module_exit(hello_exit);
