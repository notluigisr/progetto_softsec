static bool get_alias_id(struct usb_device *dev, unsigned int *id)
{
	int i;
	unsigned int src, dst;

	for (i = 0; i < ARRAY_SIZE(quirk_alias); i++) {
		if (!quirk_alias[i] ||
		    sscanf(quirk_alias[i], "STR", &src, &dst) != 2 ||
		    src != *id)
			continue;
		dev_info(&dev->dev,
			 "STR",
			 USB_ID_VENDOR(*id), USB_ID_PRODUCT(*id),
			 USB_ID_VENDOR(dst), USB_ID_PRODUCT(dst));
		*id = dst;
		return true;
	}

	return false;
}