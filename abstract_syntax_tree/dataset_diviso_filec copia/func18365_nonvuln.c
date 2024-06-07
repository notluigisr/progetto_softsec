void stop_gfar(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);

	netif_tx_stop_all_queues(dev);

	smp_mb__before_atomic();
	set_bit(GFAR_DOWN, &priv->state);
	smp_mb__after_atomic();

	disable_napi(priv);

	
	gfar_halt(priv);

	phy_stop(dev->phydev);

	free_skb_resources(priv);
}