static int mwifiex_pcie_event_complete(struct mwifiex_adapter *adapter,
				       struct sk_buff *skb)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	int ret = 0;
	u32 rdptr = card->evtbd_rdptr & MWIFIEX_EVTBD_MASK;
	u32 wrptr;
	struct mwifiex_evt_buf_desc *desc;

	if (!skb)
		return 0;

	if (rdptr >= MWIFIEX_MAX_EVT_BD) {
		mwifiex_dbg(adapter, ERROR,
			    "STR",
			    rdptr);
		return -EINVAL;
	}

	
	if (mwifiex_read_reg(adapter, reg->evt_wrptr, &wrptr)) {
		mwifiex_dbg(adapter, ERROR,
			    "STR");
		return -1;
	}

	if (!card->evt_buf_list[rdptr]) {
		skb_push(skb, adapter->intf_hdr_len);
		skb_put(skb, MAX_EVENT_SIZE - skb->len);
		if (mwifiex_map_pci_memory(adapter, skb,
					   MAX_EVENT_SIZE,
					   PCI_DMA_FROMDEVICE))
			return -1;
		card->evt_buf_list[rdptr] = skb;
		desc = card->evtbd_ring[rdptr];
		desc->paddr = MWIFIEX_SKB_DMA_ADDR(skb);
		desc->len = (u16)skb->len;
		desc->flags = 0;
		skb = NULL;
	} else {
		mwifiex_dbg(adapter, ERROR,
			    "STR",
			    rdptr, card->evt_buf_list[rdptr], skb);
	}

	if ((++card->evtbd_rdptr & MWIFIEX_EVTBD_MASK) == MWIFIEX_MAX_EVT_BD) {
		card->evtbd_rdptr = ((card->evtbd_rdptr &
					reg->evt_rollover_ind) ^
					reg->evt_rollover_ind);
	}

	mwifiex_dbg(adapter, EVENT,
		    "STR",
		    card->evtbd_rdptr, wrptr);

	
	if (mwifiex_write_reg(adapter, reg->evt_rdptr,
			      card->evtbd_rdptr)) {
		mwifiex_dbg(adapter, ERROR,
			    "STR");
		return -1;
	}

	mwifiex_dbg(adapter, EVENT,
		    "STR");
	ret = mwifiex_pcie_process_event_ready(adapter);

	return ret;
}