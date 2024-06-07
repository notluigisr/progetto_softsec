pegasus_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	pegasus_t	*pegasus = netdev_priv(dev);
	u8		reg78 = 0x04;
	int		ret;

	if (wol->wolopts & ~WOL_SUPPORTED)
		return -EINVAL;

	if (wol->wolopts & WAKE_MAGIC)
		reg78 |= 0x80;
	if (wol->wolopts & WAKE_PHY)
		reg78 |= 0x40;
	
	if (wol->wolopts)
		pegasus->eth_regs[0] |= 0x10;
	else
		pegasus->eth_regs[0] &= ~0x10;
	pegasus->wolopts = wol->wolopts;

	ret = set_register(pegasus, WakeupControl, reg78);
	if (!ret)
		ret = device_set_wakeup_enable(&pegasus->usb->dev,
						wol->wolopts);
	return ret;
}