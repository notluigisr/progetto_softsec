static inline bool is_dma_fill_aligned(struct dma_device *dev, size_t off1,
				       size_t off2, size_t len)
{
	return dmaengine_check_align(dev->fill_align, off1, off2, len);
}