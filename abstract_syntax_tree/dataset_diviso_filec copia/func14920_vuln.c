static void xenvif_fatal_tx_err(struct xenvif *vif)
{
	netdev_err(vif->dev, "STR");
	xenvif_carrier_off(vif);
}