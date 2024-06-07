static int usb_get_langid(struct usb_device *dev, unsigned char *tbuf)
{
	int err;

	if (dev->have_langid)
		return 0;

	if (dev->string_langid < 0)
		return -EPIPE;

	err = usb_string_sub(dev, 0, 0, tbuf);

	
	if (err == -ENODATA || (err > 0 && err < 4)) {
		dev->string_langid = 0x0409;
		dev->have_langid = 1;
		dev_err(&dev->dev,
			"STR");
		return 0;
	}

	
	if (err < 0) {
		dev_err(&dev->dev, "STR",
					err);
		dev->string_langid = -1;
		return -EPIPE;
	}

	
	dev->string_langid = tbuf[2] | (tbuf[3] << 8);
	dev->have_langid = 1;
	dev_dbg(&dev->dev, "STR",
				dev->string_langid);
	return 0;
}