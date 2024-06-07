int nfc_dev_up(struct nfc_dev *dev)
{
	int rc = 0;

	pr_debug("STR", dev_name(&dev->dev));

	device_lock(&dev->dev);

	if (dev->rfkill && rfkill_blocked(dev->rfkill)) {
		rc = -ERFKILL;
		goto error;
	}

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->fw_download_in_progress) {
		rc = -EBUSY;
		goto error;
	}

	if (dev->dev_up) {
		rc = -EALREADY;
		goto error;
	}

	if (dev->ops->dev_up)
		rc = dev->ops->dev_up(dev);

	if (!rc)
		dev->dev_up = true;

	
	if (dev->ops->discover_se && dev->ops->discover_se(dev))
		pr_err("STR");

error:
	device_unlock(&dev->dev);
	return rc;
}