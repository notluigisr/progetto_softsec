
static int ql_alloc_large_buffers(struct ql3_adapter *qdev)
{
	int i;
	struct ql_rcv_buf_cb *lrg_buf_cb;
	struct sk_buff *skb;
	dma_addr_t map;
	int err;

	for (i = 0; i < qdev->num_large_buffers; i++) {
		skb = netdev_alloc_skb(qdev->ndev,
				       qdev->lrg_buffer_len);
		if (unlikely(!skb)) {
			
			netdev_err(qdev->ndev,
				   "STR",
				   qdev->lrg_buffer_len * 2, i);
			ql_free_large_buffers(qdev);
			return -ENOMEM;
		} else {

			lrg_buf_cb = &qdev->lrg_buf[i];
			memset(lrg_buf_cb, 0, sizeof(struct ql_rcv_buf_cb));
			lrg_buf_cb->index = i;
			lrg_buf_cb->skb = skb;
			
			skb_reserve(skb, QL_HEADER_SPACE);
			map = pci_map_single(qdev->pdev,
					     skb->data,
					     qdev->lrg_buffer_len -
					     QL_HEADER_SPACE,
					     PCI_DMA_FROMDEVICE);

			err = pci_dma_mapping_error(qdev->pdev, map);
			if (err) {
				netdev_err(qdev->ndev,
					   "STR",
					   err);
				ql_free_large_buffers(qdev);
				return -ENOMEM;
			}

			dma_unmap_addr_set(lrg_buf_cb, mapaddr, map);
			dma_unmap_len_set(lrg_buf_cb, maplen,
					  qdev->lrg_buffer_len -
					  QL_HEADER_SPACE);
			lrg_buf_cb->buf_phy_addr_low =
			    cpu_to_le32(LS_64BITS(map));
			lrg_buf_cb->buf_phy_addr_high =
			    cpu_to_le32(MS_64BITS(map));
		}
	}
	return 0;