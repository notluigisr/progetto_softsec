int __init mon_text_init(void)
{
	struct dentry *mondir;

	mondir = debugfs_create_dir("STR", usb_debug_root);
	if (IS_ERR(mondir)) {
		
		return 0;
	}
	if (mondir == NULL) {
		printk(KERN_NOTICE TAG "STR");
		return -ENOMEM;
	}
	mon_dir = mondir;
	return 0;
}