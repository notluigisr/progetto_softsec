static void xenvif_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 * data)
{
	void *vif = netdev_priv(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(xenvif_stats); i++)
		data[i] = *(unsigned long *)(vif + xenvif_stats[i].offset);
}