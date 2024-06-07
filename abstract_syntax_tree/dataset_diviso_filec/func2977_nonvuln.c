static int macsec_change_mtu(struct net_device *dev, int new_mtu)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	unsigned int extra = macsec->secy.icv_len + macsec_extra_len(true);

	if (macsec->real_dev->mtu - extra < new_mtu)
		return -ERANGE;

	dev->mtu = new_mtu;

	return 0;
}