static int gfar_alloc_skb_resources(struct net_device *ndev)
{
	void *vaddr;
	dma_addr_t addr;
	int i, j;
	struct gfar_private *priv = netdev_priv(ndev);
	struct device *dev = priv->dev;
	struct gfar_priv_tx_q *tx_queue = NULL;
	struct gfar_priv_rx_q *rx_queue = NULL;

	priv->total_tx_ring_size = 0;
	for (i = 0; i < priv->num_tx_queues; i++)
		priv->total_tx_ring_size += priv->tx_queue[i]->tx_ring_size;

	priv->total_rx_ring_size = 0;
	for (i = 0; i < priv->num_rx_queues; i++)
		priv->total_rx_ring_size += priv->rx_queue[i]->rx_ring_size;

	
	vaddr = dma_alloc_coherent(dev,
				   (priv->total_tx_ring_size *
				    sizeof(struct txbd8)) +
				   (priv->total_rx_ring_size *
				    sizeof(struct rxbd8)),
				   &addr, GFP_KERNEL);
	if (!vaddr)
		return -ENOMEM;

	for (i = 0; i < priv->num_tx_queues; i++) {
		tx_queue = priv->tx_queue[i];
		tx_queue->tx_bd_base = vaddr;
		tx_queue->tx_bd_dma_base = addr;
		tx_queue->dev = ndev;
		
		addr  += sizeof(struct txbd8) * tx_queue->tx_ring_size;
		vaddr += sizeof(struct txbd8) * tx_queue->tx_ring_size;
	}

	
	for (i = 0; i < priv->num_rx_queues; i++) {
		rx_queue = priv->rx_queue[i];
		rx_queue->rx_bd_base = vaddr;
		rx_queue->rx_bd_dma_base = addr;
		rx_queue->ndev = ndev;
		rx_queue->dev = dev;
		addr  += sizeof(struct rxbd8) * rx_queue->rx_ring_size;
		vaddr += sizeof(struct rxbd8) * rx_queue->rx_ring_size;
	}

	
	for (i = 0; i < priv->num_tx_queues; i++) {
		tx_queue = priv->tx_queue[i];
		tx_queue->tx_skbuff =
			kmalloc_array(tx_queue->tx_ring_size,
				      sizeof(*tx_queue->tx_skbuff),
				      GFP_KERNEL);
		if (!tx_queue->tx_skbuff)
			goto cleanup;

		for (j = 0; j < tx_queue->tx_ring_size; j++)
			tx_queue->tx_skbuff[j] = NULL;
	}

	for (i = 0; i < priv->num_rx_queues; i++) {
		rx_queue = priv->rx_queue[i];
		rx_queue->rx_buff = kcalloc(rx_queue->rx_ring_size,
					    sizeof(*rx_queue->rx_buff),
					    GFP_KERNEL);
		if (!rx_queue->rx_buff)
			goto cleanup;
	}

	gfar_init_bds(ndev);

	return 0;

cleanup:
	free_skb_resources(priv);
	return -ENOMEM;
}