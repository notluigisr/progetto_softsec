static struct macsec_dev *macsec_priv(const struct net_device *dev)
{
	return (struct macsec_dev *)netdev_priv(dev);
}