static void stub_disconnect(struct usb_device *udev)
{
	struct stub_device *sdev;
	const char *udev_busid = dev_name(&udev->dev);
	struct bus_id_priv *busid_priv;
	int rc;

	dev_dbg(&udev->dev, "STR");

	busid_priv = get_busid_priv(udev_busid);
	if (!busid_priv) {
		BUG();
		return;
	}

	sdev = dev_get_drvdata(&udev->dev);

	
	if (!sdev) {
		dev_err(&udev->dev, "STR");
		return;
	}

	dev_set_drvdata(&udev->dev, NULL);

	
	stub_remove_files(&udev->dev);

	
	rc = usb_hub_release_port(udev->parent, udev->portnum,
				  (struct usb_dev_state *) udev);
	if (rc) {
		dev_dbg(&udev->dev, "STR");
		return;
	}

	
	if (usbip_in_eh(current))
		return;

	
	shutdown_busid(busid_priv);

	usb_put_dev(sdev->udev);

	
	busid_priv->sdev = NULL;
	stub_device_free(sdev);

	if (busid_priv->status == STUB_BUSID_ALLOC)
		busid_priv->status = STUB_BUSID_ADDED;
}