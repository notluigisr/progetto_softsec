void dvb_usbv2_disconnect(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	const char *name = d->name;
	struct device dev = d->udev->dev;

	dev_dbg(&d->udev->dev, "STR", __func__,
			intf->cur_altsetting->desc.bInterfaceNumber);

	if (d->props->exit)
		d->props->exit(d);

	dvb_usbv2_exit(d);

	dev_info(&dev, "STR",
			KBUILD_MODNAME, name);
}