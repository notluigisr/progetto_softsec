int line6_probe(struct usb_interface *interface,
		const struct usb_device_id *id,
		const char *driver_name,
		const struct line6_properties *properties,
		int (*private_init)(struct usb_line6 *, const struct usb_device_id *id),
		size_t data_size)
{
	struct usb_device *usbdev = interface_to_usbdev(interface);
	struct snd_card *card;
	struct usb_line6 *line6;
	int interface_number;
	int ret;

	if (WARN_ON(data_size < sizeof(*line6)))
		return -EINVAL;

	
	if (usbdev->descriptor.bNumConfigurations != 1)
		return -ENODEV;

	ret = snd_card_new(&interface->dev,
			   SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			   THIS_MODULE, data_size, &card);
	if (ret < 0)
		return ret;

	
	line6 = card->private_data;
	line6->card = card;
	line6->properties = properties;
	line6->usbdev = usbdev;
	line6->ifcdev = &interface->dev;

	strcpy(card->id, properties->id);
	strcpy(card->driver, driver_name);
	strcpy(card->shortname, properties->name);
	sprintf(card->longname, "STR", properties->name,
		dev_name(line6->ifcdev));
	card->private_free = line6_destruct;

	usb_set_intfdata(interface, line6);

	
	usb_get_dev(usbdev);

	
	dev_info(&interface->dev, "STR", properties->name);

	
	interface_number = interface->cur_altsetting->desc.bInterfaceNumber;

	
	ret = usb_set_interface(usbdev, interface_number,
				properties->altsetting);
	if (ret < 0) {
		dev_err(&interface->dev, "STR");
		goto error;
	}

	line6_get_usb_properties(line6);

	if (properties->capabilities & LINE6_CAP_CONTROL) {
		ret = line6_init_cap_control(line6);
		if (ret < 0)
			goto error;
	}

	
	ret = private_init(line6, id);
	if (ret < 0)
		goto error;

	

	dev_info(&interface->dev, "STR",
		 properties->name);

	return 0;

 error:
	
	line6_disconnect(interface);
	return ret;
}