inline void nfc_driver_failure(struct nfc_dev *dev, int err)
{
	nfc_targets_found(dev, NULL, 0);
}