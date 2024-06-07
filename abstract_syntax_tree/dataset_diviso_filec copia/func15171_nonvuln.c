static void usb_debugfs_init(void)
{
	usb_debug_root = debugfs_create_dir("STR", NULL);
	debugfs_create_file("STR", 0444, usb_debug_root, NULL,
			    &usbfs_devices_fops);
}