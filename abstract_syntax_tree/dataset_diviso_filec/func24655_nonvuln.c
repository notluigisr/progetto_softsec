static int snd_usb_mbox2_boot_quirk(struct usb_device *dev)
{
	struct usb_host_config *config = dev->actconfig;
	int err;
	u8 bootresponse[0x12];
	int fwsize;
	int count;

	fwsize = le16_to_cpu(get_cfg_desc(config)->wTotalLength);

	if (fwsize != MBOX2_FIRMWARE_SIZE) {
		dev_err(&dev->dev, "STR", fwsize);
		return -ENODEV;
	}

	dev_dbg(&dev->dev, "STR");

	count = 0;
	bootresponse[0] = MBOX2_BOOT_LOADING;
	while ((bootresponse[0] == MBOX2_BOOT_LOADING) && (count < 10)) {
		msleep(500); 
		snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			
			0x85, 0xc0, 0x0001, 0x0000, &bootresponse, 0x0012);
		if (bootresponse[0] == MBOX2_BOOT_READY)
			break;
		dev_dbg(&dev->dev, "STR");
		count++;
	}

	if (bootresponse[0] != MBOX2_BOOT_READY) {
		dev_err(&dev->dev, "STR", bootresponse[0]);
		return -ENODEV;
	}

	dev_dbg(&dev->dev, "STR");

	err = usb_get_descriptor(dev, USB_DT_DEVICE, 0,
		&dev->descriptor, sizeof(dev->descriptor));
	config = dev->actconfig;
	if (err < 0)
		dev_dbg(&dev->dev, "STR", err);

	err = usb_reset_configuration(dev);
	if (err < 0)
		dev_dbg(&dev->dev, "STR", err);
	dev_dbg(&dev->dev, "STR",
		le16_to_cpu(get_cfg_desc(config)->wTotalLength));

	mbox2_setup_48_24_magic(dev);

	dev_info(&dev->dev, "STR");

	return 0; 
}