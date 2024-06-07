int nfc_deactivate_target(struct nfc_dev *dev, u32 target_idx, u8 mode)
{
	int rc = 0;

	pr_debug("STR",
		 dev_name(&dev->dev), target_idx);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->active_target == NULL) {
		rc = -ENOTCONN;
		goto error;
	}

	if (dev->active_target->idx != target_idx) {
		rc = -ENOTCONN;
		goto error;
	}

	if (dev->ops->check_presence)
		del_timer_sync(&dev->check_pres_timer);

	dev->ops->deactivate_target(dev, dev->active_target, mode);
	dev->active_target = NULL;

error:
	device_unlock(&dev->dev);
	return rc;
}