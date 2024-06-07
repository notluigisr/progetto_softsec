int nfc_start_poll(struct nfc_dev *dev, u32 im_protocols, u32 tm_protocols)
{
	int rc;

	pr_debug("STR",
		 dev_name(&dev->dev), im_protocols, tm_protocols);

	if (!im_protocols && !tm_protocols)
		return -EINVAL;

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (!dev->dev_up) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->polling) {
		rc = -EBUSY;
		goto error;
	}

	rc = dev->ops->start_poll(dev, im_protocols, tm_protocols);
	if (!rc) {
		dev->polling = true;
		dev->rf_mode = NFC_RF_NONE;
	}

error:
	device_unlock(&dev->dev);
	return rc;
}