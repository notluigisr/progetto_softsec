static int rtl8150_set_mac_address(struct net_device *netdev, void *p)
{
	struct sockaddr *addr = p;
	rtl8150_t *dev = netdev_priv(netdev);

	if (netif_running(netdev))
		return -EBUSY;

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	netdev_dbg(netdev, "STR", netdev->dev_addr);
	
	set_registers(dev, IDR, netdev->addr_len, netdev->dev_addr);
#ifdef EEPROM_WRITE
	{
	int i;
	u8 cr;
	
	get_registers(dev, CR, 1, &cr);
	
	cr |= 0x20;
	set_registers(dev, CR, 1, &cr);
	
	for (i = 0; i * 2 < netdev->addr_len; i++) {
		set_registers(dev, IDR_EEPROM + (i * 2), 2,
		netdev->dev_addr + (i * 2));
	}
	
	cr &= 0xdf;
	set_registers(dev, CR, 1, &cr);
	}
#endif
	return 0;
}