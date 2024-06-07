static inline enum dma_status dma_async_is_complete(dma_cookie_t cookie,
			dma_cookie_t last_complete, dma_cookie_t last_used)
{
	if (last_complete <= last_used) {
		if ((cookie <= last_complete) || (cookie > last_used))
			return DMA_COMPLETE;
	} else {
		if ((cookie <= last_complete) && (cookie > last_used))
			return DMA_COMPLETE;
	}
	return DMA_IN_PROGRESS;
}