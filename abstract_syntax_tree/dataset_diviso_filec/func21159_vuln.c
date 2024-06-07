static int stub_probe(struct usb_device *udev)
{
	struct stub_device *sdev = NULL;
	const char *udev_busid = dev_name(&udev->dev);
	struct bus_id_priv *busid_priv;
	int rc;

	dev_dbg(&udev->dev, "STR");

	
	busid_priv = get_busid_priv(udev_busid);
	if (!busid_priv || (busid_priv->status == STUB_BUSID_REMOV) ||
	    (busid_priv->status == STUB_BUSID_OTHER)) {
		dev_info(&udev->dev,
			"STR",
			udev_busid);

		
		return -ENODEV;
	}

	if (udev->descriptor.bDeviceClass == USB_CLASS_HUB) {
		dev_dbg(&udev->dev, "STR",
			 udev_busid);
		return -ENODEV;
	}

	if (!strcmp(udev->bus->bus_name, "STR")) {
		dev_dbg(&udev->dev,
			"STR",
			udev_busid);

		return -ENODEV;
	}

	
	sdev = stub_device_alloc(udev);
	if (!sdev)
		return -ENOMEM;

	dev_info(&udev->dev,
		"STR",
		udev->bus->busnum, udev->devnum);

	busid_priv->shutdown_busid = 0;

	
	dev_set_drvdata(&udev->dev, sdev);
	busid_priv->sdev = sdev;
	busid_priv->udev = udev;

	
	rc = usb_hub_claim_port(udev->parent, udev->portnum,
			(struct usb_dev_state *) udev);
	if (rc) {
		dev_dbg(&udev->dev, "STR");
		goto err_port;
	}

	rc = stub_add_files(&udev->dev);
	if (rc) {
		dev_err(&udev->dev, "STR", udev_busid);
		goto err_files;
	}
	busid_priv->status = STUB_BUSID_ALLOC;

	return 0;
err_files:
	usb_hub_release_port(udev->parent, udev->portnum,
			     (struct usb_dev_state *) udev);
err_port:
	dev_set_drvdata(&udev->dev, NULL);
	usb_put_dev(udev);

	busid_priv->sdev = NULL;
	stub_device_free(sdev);
	return rc;
}