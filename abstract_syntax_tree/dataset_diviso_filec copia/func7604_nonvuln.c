ioat2_dma_prep_memcpy_lock(struct dma_chan *c, dma_addr_t dma_dest,
			   dma_addr_t dma_src, size_t len, unsigned long flags)
{
	struct ioat2_dma_chan *ioat = to_ioat2_chan(c);
	struct ioat_dma_descriptor *hw;
	struct ioat_ring_ent *desc;
	dma_addr_t dst = dma_dest;
	dma_addr_t src = dma_src;
	size_t total_len = len;
	int num_descs, idx, i;

	num_descs = ioat2_xferlen_to_descs(ioat, len);
	if (likely(num_descs) && ioat2_check_space_lock(ioat, num_descs) == 0)
		idx = ioat->head;
	else
		return NULL;
	i = 0;
	do {
		size_t copy = min_t(size_t, len, 1 << ioat->xfercap_log);

		desc = ioat2_get_ring_ent(ioat, idx + i);
		hw = desc->hw;

		hw->size = copy;
		hw->ctl = 0;
		hw->src_addr = src;
		hw->dst_addr = dst;

		len -= copy;
		dst += copy;
		src += copy;
		dump_desc_dbg(ioat, desc);
	} while (++i < num_descs);

	desc->txd.flags = flags;
	desc->len = total_len;
	hw->ctl_f.int_en = !!(flags & DMA_PREP_INTERRUPT);
	hw->ctl_f.fence = !!(flags & DMA_PREP_FENCE);
	hw->ctl_f.compl_write = 1;
	dump_desc_dbg(ioat, desc);
	

	return &desc->txd;
}