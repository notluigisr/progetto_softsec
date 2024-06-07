static int usb_enumerate_device(struct usb_device *udev)
{
	int err;
	struct usb_hcd *hcd = bus_to_hcd(udev->bus);

	if (udev->config == NULL) {
		err = usb_get_configuration(udev);
		if (err < 0) {
			if (err != -ENODEV)
				dev_err(&udev->dev, "STR",
						err);
			return err;
		}
	}

	
	udev->product = usb_cache_string(udev, udev->descriptor.iProduct);
	udev->manufacturer = usb_cache_string(udev,
					      udev->descriptor.iManufacturer);
	udev->serial = usb_cache_string(udev, udev->descriptor.iSerialNumber);

	err = usb_enumerate_device_otg(udev);
	if (err < 0)
		return err;

	if (IS_ENABLED(CONFIG_USB_OTG_WHITELIST) && hcd->tpl_support &&
		!is_targeted(udev)) {
		
		if (IS_ENABLED(CONFIG_USB_OTG) && (udev->bus->b_hnp_enable
			|| udev->bus->is_b_host)) {
			err = usb_port_suspend(udev, PMSG_AUTO_SUSPEND);
			if (err < 0)
				dev_dbg(&udev->dev, "STR", err);
		}
		return -ENOTSUPP;
	}

	usb_detect_interface_quirks(udev);

	return 0;
}