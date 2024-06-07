static int mwifiex_pcie_alloc_cmdrsp_buf(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	struct sk_buff *skb;

	
	skb = dev_alloc_skb(MWIFIEX_UPLD_SIZE);
	if (!skb) {
		mwifiex_dbg(adapter, ERROR,
			    "STR");
		return -ENOMEM;
	}
	skb_put(skb, MWIFIEX_UPLD_SIZE);
	if (mwifiex_map_pci_memory(adapter, skb, MWIFIEX_UPLD_SIZE,
				   PCI_DMA_FROMDEVICE))
		return -1;

	card->cmdrsp_buf = skb;

	return 0;
}