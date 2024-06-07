static void destroy_usb_class(void)
{
	mutex_lock(&init_usb_class_mutex);
	kref_put(&usb_class->kref, release_usb_class);
	mutex_unlock(&init_usb_class_mutex);
}