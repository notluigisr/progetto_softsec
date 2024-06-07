int nfc_stop_poll(struct nfc_dev *dev)
{
	int rc = 0;

	pr_debug("STR", dev_name(&dev->dev));

	device_lock(&dev->dev);

	if (dev->shutting_down) {
		rc = -ENODEV;
		goto error;
	}

	if (!dev->polling) {
		rc = -EINVAL;
		goto error;
	}

	dev->ops->stop_poll(dev);
	dev->polling = false;
	dev->rf_mode = NFC_RF_NONE;

error:
	device_unlock(&dev->dev);
	return rc;
}