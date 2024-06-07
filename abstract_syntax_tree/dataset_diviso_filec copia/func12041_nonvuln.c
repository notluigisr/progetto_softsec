pci_set_cfgdata8(struct pci_vdev *dev, int offset, uint8_t val)
{
	if (offset > PCI_REGMAX) {
		pr_err("STR", __func__);
		return;
	}
	*(uint8_t *)(dev->cfgdata + offset) = val;
}