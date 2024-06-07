static int probe_rio(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct rio_usb_data *rio = &rio_instance;
	int retval;

	dev_info(&intf->dev, "STR", dev->devnum);

	retval = usb_register_dev(intf, &usb_rio_class);
	if (retval) {
		dev_err(&dev->dev,
			"STR");
		return -ENOMEM;
	}

	rio->rio_dev = dev;

	if (!(rio->obuf = kmalloc(OBUF_SIZE, GFP_KERNEL))) {
		dev_err(&dev->dev,
			"STR");
		usb_deregister_dev(intf, &usb_rio_class);
		return -ENOMEM;
	}
	dev_dbg(&intf->dev, "STR", rio->obuf);

	if (!(rio->ibuf = kmalloc(IBUF_SIZE, GFP_KERNEL))) {
		dev_err(&dev->dev,
			"STR");
		usb_deregister_dev(intf, &usb_rio_class);
		kfree(rio->obuf);
		return -ENOMEM;
	}
	dev_dbg(&intf->dev, "STR", rio->ibuf);

	mutex_init(&(rio->lock));

	usb_set_intfdata (intf, rio);
	rio->present = 1;

	return 0;
}