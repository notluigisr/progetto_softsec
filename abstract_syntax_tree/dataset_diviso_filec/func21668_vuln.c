int ar6000_create_ap_interface(struct ar6_softc *ar, char *ap_ifname)
{
    struct net_device *dev;
    struct ar_virtual_interface *arApDev;

    dev = alloc_etherdev(sizeof(struct ar_virtual_interface));
    if (dev == NULL) {
        AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("STR"));
        return A_ERROR;
    } 
    
    ether_setup(dev);
    init_netdev(dev, ap_ifname);

    if (register_netdev(dev)) {
        AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("STR"));
        return A_ERROR;
    }

    arApDev = netdev_priv(dev);
    arApDev->arDev = ar;
    arApDev->arNetDev = dev;
    arApDev->arStaNetDev = ar->arNetDev;

    ar->arApDev = arApDev;
    arApNetDev = dev;

    
    memcpy(dev->dev_addr, ar->arNetDev->dev_addr, AR6000_ETH_ADDR_LEN);

    return 0;
}