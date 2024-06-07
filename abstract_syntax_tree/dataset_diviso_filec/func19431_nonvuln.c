static netdev_features_t i40e_features_check(struct sk_buff *skb,
					     struct net_device *dev,
					     netdev_features_t features)
{
	size_t len;

	
	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return features;

	
	if (skb_is_gso(skb) && (skb_shinfo(skb)->gso_size < 64))
		features &= ~NETIF_F_GSO_MASK;

	
	len = skb_network_header(skb) - skb->data;
	if (len & ~(63 * 2))
		goto out_err;

	
	len = skb_transport_header(skb) - skb_network_header(skb);
	if (len & ~(127 * 4))
		goto out_err;

	if (skb->encapsulation) {
		
		len = skb_inner_network_header(skb) - skb_transport_header(skb);
		if (len & ~(127 * 2))
			goto out_err;

		
		len = skb_inner_transport_header(skb) -
		      skb_inner_network_header(skb);
		if (len & ~(127 * 4))
			goto out_err;
	}

	

	return features;
out_err:
	return features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
}