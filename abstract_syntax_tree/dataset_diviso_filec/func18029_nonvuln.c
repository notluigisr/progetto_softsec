static inline struct mcba_usb_ctx *mcba_usb_get_free_ctx(struct mcba_priv *priv,
							 struct can_frame *cf)
{
	int i = 0;
	struct mcba_usb_ctx *ctx = NULL;

	for (i = 0; i < MCBA_MAX_TX_URBS; i++) {
		if (priv->tx_context[i].ndx == MCBA_CTX_FREE) {
			ctx = &priv->tx_context[i];
			ctx->ndx = i;

			if (cf)
				ctx->can = true;
			else
				ctx->can = false;

			atomic_dec(&priv->free_ctx_cnt);
			break;
		}
	}

	if (!atomic_read(&priv->free_ctx_cnt))
		
		netif_stop_queue(priv->netdev);

	return ctx;
}