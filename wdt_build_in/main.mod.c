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

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7ef3190f, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x1b73d11e, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x6f01373e, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x641b7b9c, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x7952ec47, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x1e322e62, __VMLINUX_SYMBOL_STR(watchdog_register_device) },
	{ 0x62697525, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x56964b65, __VMLINUX_SYMBOL_STR(watchdog_init_timeout) },
	{ 0x62581107, __VMLINUX_SYMBOL_STR(devm_ioremap_resource) },
	{ 0x8d04b6, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xd80c3e93, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x32f33407, __VMLINUX_SYMBOL_STR(watchdog_unregister_device) },
	{ 0x6206b84e, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0xe261727c, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x5828c9d0, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cti,omap3-wdt");
MODULE_ALIAS("of:N*T*Cti,omap3-wdtC*");
