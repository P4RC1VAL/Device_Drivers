int init_module( void ) {
printk(KERN_INFO "\nInstalling %s (major=%d) \n", modname,my_major );
devp = pci_find_device( VENDOR_ID, DEVICE_ID, devp );
if ( !devp ) return -ENODEV;
irq = devp->irq;
iobase = pci_resource_start( devp, 0 ); // Используем BAR0
outb( 0x10, iobase + 0x37 );
// Сбросить сетевой интерфейс
printk( "RealTek 8139 Network Interface: iobase=%04X \n", iobase );
while ( inb( iobase + 0x37 ) & 0x10 );
init_waitqueue_head( &wq );
if ( request_irq( irq, my_isr, IRQF_SHARED, devname, &devname ) )
return -EBUSY;
kmem = kmalloc( KBUFSIZ, GFP_KERNEL );
if ( !kmem ) return -ENOMEM;
kmem_base = __pa( kmem );
kmem_size = KBUFSIZ;
printk( "Physical address-range of kernel buffer: " );
printk( "%08lX-%08lX \n", kmem_base, kmem_base+kmem_size );
outl( kmem_base, iobase + 0x30 ); // Передать адрес приемного буфера в RBStart
return register_chrdev( my_major, devname, &my_fops );
}
