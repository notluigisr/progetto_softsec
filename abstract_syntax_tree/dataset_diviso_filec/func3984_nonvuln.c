brcmf_msgbuf_alloc_pktid(struct device *dev,
			 struct brcmf_msgbuf_pktids *pktids,
			 struct sk_buff *skb, u16 data_offset,
			 dma_addr_t *physaddr, u32 *idx)
{
	struct brcmf_msgbuf_pktid *array;
	u32 count;

	array = pktids->array;

	*physaddr = dma_map_single(dev, skb->data + data_offset,
				   skb->len - data_offset, pktids->direction);

	if (dma_mapping_error(dev, *physaddr)) {
		brcmf_err("STR");
		return -ENOMEM;
	}

	*idx = pktids->last_allocated_idx;

	count = 0;
	do {
		(*idx)++;
		if (*idx == pktids->array_size)
			*idx = 0;
		if (array[*idx].allocated.counter == 0)
			if (atomic_cmpxchg(&array[*idx].allocated, 0, 1) == 0)
				break;
		count++;
	} while (count < pktids->array_size);

	if (count == pktids->array_size)
		return -ENOMEM;

	array[*idx].data_offset = data_offset;
	array[*idx].physaddr = *physaddr;
	array[*idx].skb = skb;

	pktids->last_allocated_idx = *idx;

	return 0;
}