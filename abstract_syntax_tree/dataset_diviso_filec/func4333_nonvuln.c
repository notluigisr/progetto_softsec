static inline void mcba_usb_free_ctx(struct mcba_usb_ctx *ctx)
{
	
	atomic_inc(&ctx->priv->free_ctx_cnt);

	ctx->ndx = MCBA_CTX_FREE;

	
	netif_wake_queue(ctx->priv->netdev);
}