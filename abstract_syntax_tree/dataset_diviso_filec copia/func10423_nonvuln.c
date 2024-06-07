static void dev_queue_xmit_nit(struct sk_buff *skb, struct net_device *dev)
{
	struct packet_type *ptype;

#ifdef CONFIG_NET_CLS_ACT
	if (!(skb->tstamp.tv64 && (G_TC_FROM(skb->tc_verd) & AT_INGRESS)))
		net_timestamp_set(skb);
#else
	net_timestamp_set(skb);
#endif

	rcu_read_lock();
	list_for_each_entry_rcu(ptype, &ptype_all, list) {
		
		if ((ptype->dev == dev || !ptype->dev) &&
		    (ptype->af_packet_priv == NULL ||
		     (struct sock *)ptype->af_packet_priv != skb->sk)) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
			if (!skb2)
				break;

			
			skb_reset_mac_header(skb2);

			if (skb_network_header(skb2) < skb2->data ||
			    skb2->network_header > skb2->tail) {
				if (net_ratelimit())
					printk(KERN_CRIT "STR"
					       "STR",
					       ntohs(skb2->protocol),
					       dev->name);
				skb_reset_network_header(skb2);
			}

			skb2->transport_header = skb2->network_header;
			skb2->pkt_type = PACKET_OUTGOING;
			ptype->func(skb2, skb->dev, ptype, skb->dev);
		}
	}
	rcu_read_unlock();
}