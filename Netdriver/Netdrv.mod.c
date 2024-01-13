#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xcb440b5e, "module_layout" },
	{ 0x7bc72124, "eth_validate_addr" },
	{ 0x2b2bd200, "platform_driver_unregister" },
	{ 0x4797fac4, "__platform_driver_register" },
	{ 0x6c0888f4, "register_netdev" },
	{ 0x9ca14e85, "alloc_etherdev_mqs" },
	{ 0x9a6ca887, "devm_kmalloc" },
	{ 0xbf5edb26, "consume_skb" },
	{ 0x9b5cc715, "skb_tstamp_tx" },
	{ 0xad5b371a, "skb_clone_tx_timestamp" },
	{ 0xa715db6d, "free_netdev" },
	{ 0x9a1f7f85, "unregister_netdev" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A5C0B6028890D942B1050F7");
