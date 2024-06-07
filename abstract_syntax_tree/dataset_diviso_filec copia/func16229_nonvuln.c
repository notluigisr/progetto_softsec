mii_set_media_pcs (struct net_device *dev)
{
	__u16 bmcr;
	__u16 esr;
	__u16 anar;
	int phy_addr;
	struct netdev_private *np;
	np = netdev_priv(dev);
	phy_addr = np->phy_addr;

	
	if (np->an_enable) {
		
		esr = mii_read (dev, phy_addr, PCS_ESR);
		anar = mii_read (dev, phy_addr, MII_ADVERTISE) &
			~PCS_ANAR_HALF_DUPLEX &
			~PCS_ANAR_FULL_DUPLEX;
		if (esr & (MII_ESR_1000BT_HD | MII_ESR_1000BX_HD))
			anar |= PCS_ANAR_HALF_DUPLEX;
		if (esr & (MII_ESR_1000BT_FD | MII_ESR_1000BX_FD))
			anar |= PCS_ANAR_FULL_DUPLEX;
		anar |= PCS_ANAR_PAUSE | PCS_ANAR_ASYMMETRIC;
		mii_write (dev, phy_addr, MII_ADVERTISE, anar);

		
		mii_write (dev, phy_addr, MII_BMCR, BMCR_RESET);
		bmcr = BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET;
		mii_write (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(1);
	} else {
		
		
		bmcr = BMCR_RESET;
		mii_write (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(10);
		if (np->full_duplex) {
			bmcr = BMCR_FULLDPLX;
			printk (KERN_INFO "STR");
		} else {
			bmcr = 0;
			printk (KERN_INFO "STR");
		}
		mii_write (dev, phy_addr, MII_BMCR, bmcr);
		mdelay(10);

		
		mii_write (dev, phy_addr, MII_ADVERTISE, 0);
	}
	return 0;
}