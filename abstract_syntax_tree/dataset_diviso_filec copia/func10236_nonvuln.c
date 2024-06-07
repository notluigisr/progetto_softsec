dma_wait_for_async_tx(struct dma_async_tx_descriptor *tx)
{
	unsigned long dma_sync_wait_timeout = jiffies + msecs_to_jiffies(5000);

	if (!tx)
		return DMA_COMPLETE;

	while (tx->cookie == -EBUSY) {
		if (time_after_eq(jiffies, dma_sync_wait_timeout)) {
			pr_err("STR",
			       __func__);
			return DMA_ERROR;
		}
		cpu_relax();
	}
	return dma_sync_wait(tx->chan, tx->cookie);
}