int usb_register_dev(struct usb_interface *intf,
		     struct usb_class_driver *class_driver)
{
	int retval;
	int minor_base = class_driver->minor_base;
	int minor;
	char name[20];

#ifdef CONFIG_USB_DYNAMIC_MINORS
	
	minor_base = 0;
#endif

	if (class_driver->fops == NULL)
		return -EINVAL;
	if (intf->minor >= 0)
		return -EADDRINUSE;

	mutex_lock(&init_usb_class_mutex);
	retval = init_usb_class();
	mutex_unlock(&init_usb_class_mutex);

	if (retval)
		return retval;

	dev_dbg(&intf->dev, "STR", minor_base);

	down_write(&minor_rwsem);
	for (minor = minor_base; minor < MAX_USB_MINORS; ++minor) {
		if (usb_minors[minor])
			continue;

		usb_minors[minor] = class_driver->fops;
		intf->minor = minor;
		break;
	}
	up_write(&minor_rwsem);
	if (intf->minor < 0)
		return -EXFULL;

	
	snprintf(name, sizeof(name), class_driver->name, minor - minor_base);
	intf->usb_dev = device_create(usb_class->class, &intf->dev,
				      MKDEV(USB_MAJOR, minor), class_driver,
				      "STR", kbasename(name));
	if (IS_ERR(intf->usb_dev)) {
		down_write(&minor_rwsem);
		usb_minors[minor] = NULL;
		intf->minor = -1;
		up_write(&minor_rwsem);
		retval = PTR_ERR(intf->usb_dev);
	}
	return retval;
}