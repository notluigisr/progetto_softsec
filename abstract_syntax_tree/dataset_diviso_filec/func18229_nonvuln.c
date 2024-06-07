int xenvif_connect(struct xenvif *vif, unsigned long tx_ring_ref,
		   unsigned long rx_ring_ref, unsigned int evtchn)
{
	int err = -ENOMEM;

	
	if (vif->irq)
		return 0;

	err = xen_netbk_map_frontend_rings(vif, tx_ring_ref, rx_ring_ref);
	if (err < 0)
		goto err;

	err = bind_interdomain_evtchn_to_irqhandler(
		vif->domid, evtchn, xenvif_interrupt, 0,
		vif->dev->name, vif);
	if (err < 0)
		goto err_unmap;
	vif->irq = err;
	disable_irq(vif->irq);

	xenvif_get(vif);

	rtnl_lock();
	if (!vif->can_sg && vif->dev->mtu > ETH_DATA_LEN)
		dev_set_mtu(vif->dev, ETH_DATA_LEN);
	netdev_update_features(vif->dev);
	netif_carrier_on(vif->dev);
	if (netif_running(vif->dev))
		xenvif_up(vif);
	rtnl_unlock();

	return 0;
err_unmap:
	xen_netbk_unmap_frontend_rings(vif);
err:
	return err;
}