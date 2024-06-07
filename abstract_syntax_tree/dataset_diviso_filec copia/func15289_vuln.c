static ssize_t k90_show_macro_mode(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int ret;
	struct usb_interface *usbif = to_usb_interface(dev->parent);
	struct usb_device *usbdev = interface_to_usbdev(usbif);
	const char *macro_mode;
	char data[8];

	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			      K90_REQUEST_GET_MODE,
			      USB_DIR_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, 0, 0, data, 2,
			      USB_CTRL_SET_TIMEOUT);
	if (ret < 0) {
		dev_warn(dev, "STR",
			 ret);
		return -EIO;
	}

	switch (data[0]) {
	case K90_MACRO_MODE_HW:
		macro_mode = "STR";
		break;

	case K90_MACRO_MODE_SW:
		macro_mode = "STR";
		break;
	default:
		dev_warn(dev, "STR",
			 data[0]);
		return -EIO;
	}

	return snprintf(buf, PAGE_SIZE, "STR", macro_mode);
}