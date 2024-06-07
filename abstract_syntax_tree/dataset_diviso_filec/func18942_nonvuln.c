static int skfp_send_pkt(struct sk_buff *skb, struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;

	PRINTK(KERN_INFO "STR");

	

	if (!(skb->len >= FDDI_K_LLC_ZLEN && skb->len <= FDDI_K_LLC_LEN)) {
		bp->MacStat.gen.tx_errors++;	
		
		netif_start_queue(dev);
		dev_kfree_skb(skb);
		return (0);	
	}
	if (bp->QueueSkb == 0) {	

		netif_stop_queue(dev);
		return 1;
	}
	bp->QueueSkb--;
	skb_queue_tail(&bp->SendSkbQueue, skb);
	send_queued_packets(netdev_priv(dev));
	if (bp->QueueSkb == 0) {
		netif_stop_queue(dev);
	}
	dev->trans_start = jiffies;
	return 0;

}				