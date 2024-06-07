static inline struct dma_async_tx_descriptor *dmaengine_prep_slave_sg(
	struct dma_chan *chan, struct scatterlist *sgl,	unsigned int sg_len,
	enum dma_transfer_direction dir, unsigned long flags)
{
	return chan->device->device_prep_slave_sg(chan, sgl, sg_len,
						  dir, flags, NULL);
}