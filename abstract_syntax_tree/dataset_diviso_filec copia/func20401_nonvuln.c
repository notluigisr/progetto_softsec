static inline int dma_maxpq(struct dma_device *dma, enum dma_ctrl_flags flags)
{
	if (dma_dev_has_pq_continue(dma) || !dmaf_continue(flags))
		return dma_dev_to_maxpq(dma);
	else if (dmaf_p_disabled_continue(flags))
		return dma_dev_to_maxpq(dma) - 1;
	else if (dmaf_continue(flags))
		return dma_dev_to_maxpq(dma) - 3;
	BUG();
}