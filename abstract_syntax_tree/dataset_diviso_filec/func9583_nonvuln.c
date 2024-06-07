static int sd_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	const struct sd_desc *desc = &sd_desc;

	switch (id->driver_info) {
	case CIT_MODEL0:
	case CIT_MODEL1:
		if (intf->cur_altsetting->desc.bInterfaceNumber != 2)
			return -ENODEV;
		break;
	case CIT_MODEL2:
	case CIT_MODEL4:
		if (intf->cur_altsetting->desc.bInterfaceNumber != 0)
			return -ENODEV;
		break;
	case CIT_MODEL3:
		if (intf->cur_altsetting->desc.bInterfaceNumber != 0)
			return -ENODEV;
		
		if (ibm_netcam_pro)
			desc = &sd_desc_isoc_nego;
		break;
	}

	return gspca_dev_probe2(intf, id, desc, sizeof(struct sd), THIS_MODULE);
}