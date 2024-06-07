static struct sk_buff **tcp6_gro_receive(struct sk_buff **head,
					 struct sk_buff *skb)
{
	const struct ipv6hdr *iph = skb_gro_network_header(skb);

	switch (skb->ip_summed) {
	case CHECKSUM_COMPLETE:
		if (!tcp_v6_check(skb_gro_len(skb), &iph->saddr, &iph->daddr,
				  skb->csum)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			break;
		}

		
	case CHECKSUM_NONE:
		NAPI_GRO_CB(skb)->flush = 1;
		return NULL;
	}

	return tcp_gro_receive(head, skb);
}