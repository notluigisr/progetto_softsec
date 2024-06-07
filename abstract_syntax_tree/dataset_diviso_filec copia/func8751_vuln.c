void nfc_unregister_device(struct nfc_dev *dev)
{
	int rc;

	pr_debug("STR", dev_name(&dev->dev));

	if (dev->rfkill) {
		rfkill_unregister(dev->rfkill);
		rfkill_destroy(dev->rfkill);
	}

	if (dev->ops->check_presence) {
		device_lock(&dev->dev);
		dev->shutting_down = true;
		device_unlock(&dev->dev);
		del_timer_sync(&dev->check_pres_timer);
		cancel_work_sync(&dev->check_pres_work);
	}

	rc = nfc_genl_device_removed(dev);
	if (rc)
		pr_debug("STR"
			 "STR", dev_name(&dev->dev));

	nfc_llcp_unregister_device(dev);

	mutex_lock(&nfc_devlist_mutex);
	nfc_devlist_generation++;
	device_del(&dev->dev);
	mutex_unlock(&nfc_devlist_mutex);
}