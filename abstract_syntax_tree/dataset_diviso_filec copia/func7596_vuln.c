int nfc_activate_target(struct nfc_dev *dev, u32 target_idx, u32 protocol)
{
	int rc;
	struct nfc_target *target;

	pr_debug("STR",
		 dev_name(&dev->dev), target_idx, protocol);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->active_target) {
		rc = -EBUSY;
		goto error;
	}

	target = nfc_find_target(dev, target_idx);
	if (target == NULL) {
		rc = -ENOTCONN;
		goto error;
	}

	rc = dev->ops->activate_target(dev, target, protocol);
	if (!rc) {
		dev->active_target = target;
		dev->rf_mode = NFC_RF_INITIATOR;

		if (dev->ops->check_presence && !dev->shutting_down)
			mod_timer(&dev->check_pres_timer, jiffies +
				  msecs_to_jiffies(NFC_CHECK_PRES_FREQ_MS));
	}

error:
	device_unlock(&dev->dev);
	return rc;
}