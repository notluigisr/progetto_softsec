static __init int selinux_init(void)
{
	if (!security_module_enable(&selinux_ops)) {
		selinux_enabled = 0;
		return 0;
	}

	if (!selinux_enabled) {
		printk(KERN_INFO "STR");
		return 0;
	}

	printk(KERN_INFO "STR");

	
	cred_init_security();

	default_noexec = !(VM_DATA_DEFAULT_FLAGS & VM_EXEC);

	sel_inode_cache = kmem_cache_create("STR",
					    sizeof(struct inode_security_struct),
					    0, SLAB_PANIC, NULL);
	avc_init();

	if (register_security(&selinux_ops))
		panic("STR");

	if (avc_add_callback(selinux_netcache_avc_callback, AVC_CALLBACK_RESET))
		panic("STR");

	if (selinux_enforcing)
		printk(KERN_DEBUG "STR");
	else
		printk(KERN_DEBUG "STR");

	return 0;
}