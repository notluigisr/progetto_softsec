int nfc_fw_download(struct nfc_dev *dev, const char *firmware_name)
{
	int rc = 0;

	pr_debug("STR", dev_name(&dev->dev), firmware_name);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->dev_up) {
		rc = -EBUSY;
		goto error;
	}

	if (!dev->ops->fw_download) {
		rc = -EOPNOTSUPP;
		goto error;
	}

	dev->fw_download_in_progress = true;
	rc = dev->ops->fw_download(dev, firmware_name);
	if (rc)
		dev->fw_download_in_progress = false;

error:
	device_unlock(&dev->dev);
	return rc;
}