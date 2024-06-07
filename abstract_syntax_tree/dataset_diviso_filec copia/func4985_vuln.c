static int gs_usb_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct gs_usb *dev;
	int rc = -ENOMEM;
	unsigned int icount, i;
	struct gs_host_config hconf = {
		.byte_order = 0x0000beef,
	};
	struct gs_device_config dconf;

	
	rc = usb_control_msg(interface_to_usbdev(intf),
			     usb_sndctrlpipe(interface_to_usbdev(intf), 0),
			     GS_USB_BREQ_HOST_FORMAT,
			     USB_DIR_OUT|USB_TYPE_VENDOR|USB_RECIP_INTERFACE,
			     1,
			     intf->altsetting[0].desc.bInterfaceNumber,
			     &hconf,
			     sizeof(hconf),
			     1000);

	if (rc < 0) {
		dev_err(&intf->dev, "STR",
			rc);
		return rc;
	}

	
	rc = usb_control_msg(interface_to_usbdev(intf),
			     usb_rcvctrlpipe(interface_to_usbdev(intf), 0),
			     GS_USB_BREQ_DEVICE_CONFIG,
			     USB_DIR_IN|USB_TYPE_VENDOR|USB_RECIP_INTERFACE,
			     1,
			     intf->altsetting[0].desc.bInterfaceNumber,
			     &dconf,
			     sizeof(dconf),
			     1000);
	if (rc < 0) {
		dev_err(&intf->dev, "STR",
			rc);
		return rc;
	}

	icount = dconf.icount + 1;
	dev_info(&intf->dev, "STR", icount);

	if (icount > GS_MAX_INTF) {
		dev_err(&intf->dev,
			"STR",
			GS_MAX_INTF);
		return -EINVAL;
	}

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	init_usb_anchor(&dev->rx_submitted);

	atomic_set(&dev->active_channels, 0);

	usb_set_intfdata(intf, dev);
	dev->udev = interface_to_usbdev(intf);

	for (i = 0; i < icount; i++) {
		dev->canch[i] = gs_make_candev(i, intf, &dconf);
		if (IS_ERR_OR_NULL(dev->canch[i])) {
			
			rc = PTR_ERR(dev->canch[i]);

			
			icount = i;
			for (i = 0; i < icount; i++)
				gs_destroy_candev(dev->canch[i]);

			usb_kill_anchored_urbs(&dev->rx_submitted);
			kfree(dev);
			return rc;
		}
		dev->canch[i]->parent = dev;
	}

	return 0;
}