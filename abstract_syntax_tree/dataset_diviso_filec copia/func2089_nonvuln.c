static void gfar_filer_config_wol(struct gfar_private *priv)
{
	unsigned int i;
	u32 rqfcr;

	__gfar_filer_disable(priv);

	
	rqfcr = RQFCR_RJE | RQFCR_CMP_MATCH;
	for (i = 0; i <= MAX_FILER_IDX; i++)
		gfar_write_filer(priv, i, rqfcr, 0);

	i = 0;
	if (priv->wol_opts & GFAR_WOL_FILER_UCAST) {
		
		struct net_device *ndev = priv->ndev;
		
		u8 qindex = (u8)priv->gfargrp[0].rx_queue->qindex;
		u32 dest_mac_addr = (ndev->dev_addr[0] << 16) |
				    (ndev->dev_addr[1] << 8) |
				     ndev->dev_addr[2];

		rqfcr = (qindex << 10) | RQFCR_AND |
			RQFCR_CMP_EXACT | RQFCR_PID_DAH;

		gfar_write_filer(priv, i++, rqfcr, dest_mac_addr);

		dest_mac_addr = (ndev->dev_addr[3] << 16) |
				(ndev->dev_addr[4] << 8) |
				 ndev->dev_addr[5];
		rqfcr = (qindex << 10) | RQFCR_GPI |
			RQFCR_CMP_EXACT | RQFCR_PID_DAL;
		gfar_write_filer(priv, i++, rqfcr, dest_mac_addr);
	}

	__gfar_filer_enable(priv);
}