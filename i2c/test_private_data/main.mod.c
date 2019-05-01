#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
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
__used
__attribute__((section("__versions"))) = {
	{ 0x977e40b4, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x7bded033, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xdc273cf3, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0x1beff1cf, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xa3a1c32e, __VMLINUX_SYMBOL_STR(i2c_put_adapter) },
	{ 0x9e2bb471, __VMLINUX_SYMBOL_STR(i2c_new_device) },
	{ 0xb017bed9, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0x65d5bf5b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x53dc68, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xaf250583, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x88c259e1, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x9491b702, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xca72bedc, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x339b7a65, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xa25b0404, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x67cdb1f7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xf281db68, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x8f678b07, __VMLINUX_SYMBOL_STR(__stack_chk_guard) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:lcd_i2c");
