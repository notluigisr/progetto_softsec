
static void netif_free_tx_queues(struct net_device *dev)
{
	if (is_vmalloc_addr(dev->_tx))
		vfree(dev->_tx);
	else
		kfree(dev->_tx);