int nfc_dep_link_up(struct nfc_dev *dev, int target_index, u8 comm_mode)
{
	int rc = 0;
	u8 *gb;
	size_t gb_len;
	struct nfc_target *target;

	pr_debug("STR", dev_name(&dev->dev), comm_mode);

	if (!dev->ops->dep_link_up)
		return -EOPNOTSUPP;

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->dep_link_up == true) {
		rc = -EALREADY;
		goto error;
	}

	gb = nfc_llcp_general_bytes(dev, &gb_len);
	if (gb_len > NFC_MAX_GT_LEN) {
		rc = -EINVAL;
		goto error;
	}

	target = nfc_find_target(dev, target_index);
	if (target == NULL) {
		rc = -ENOTCONN;
		goto error;
	}

	rc = dev->ops->dep_link_up(dev, target, comm_mode, gb, gb_len);
	if (!rc) {
		dev->active_target = target;
		dev->rf_mode = NFC_RF_INITIATOR;
	}

error:
	device_unlock(&dev->dev);
	return rc;
}