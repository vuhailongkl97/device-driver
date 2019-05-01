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
	{ 0x88c259e1, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x5f02b70f, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x7bded033, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xf281db68, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xaf250583, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xbaba2c5b, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x8f85d98b, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x9929e62c, __VMLINUX_SYMBOL_STR(i2c_smbus_write_word_data) },
	{ 0x144bb13e, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x65d5bf5b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x34fa7203, __VMLINUX_SYMBOL_STR(i2c_smbus_read_word_data) },
	{ 0xcd9cf5d0, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xca72bedc, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x1beff1cf, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x53dc68, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xa25b0404, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x67cdb1f7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb2ae2a7e, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9491b702, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x8f678b07, __VMLINUX_SYMBOL_STR(__stack_chk_guard) },
	{ 0x339b7a65, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

