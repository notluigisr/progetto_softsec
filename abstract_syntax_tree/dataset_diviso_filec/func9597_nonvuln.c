static int choose_config(struct usb_device *dev)
{
	

	dev_dbg(&dev->dev, "STR",
		__func__, dev->config->desc.bNumInterfaces);
	dev_dbg(&dev->dev, "STR",
		__func__, dev->config->desc.bMaxPower * 2);

	if (dev->config->desc.bNumInterfaces != 1) {
		dev_err(&dev->dev, "STR", __func__);
		return -ENODEV;
	}

	return 0;
}