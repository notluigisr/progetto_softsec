static struct sk_buff *ipv6_gso_segment(struct sk_buff *skb,
	netdev_features_t features)
{
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	struct ipv6hdr *ipv6h;
	const struct net_offload *ops;
	int proto;
	struct frag_hdr *fptr;
	unsigned int unfrag_ip6hlen;
	unsigned int payload_len;
	u8 *prevhdr;
	int offset = 0;
	bool encap, udpfrag;
	int nhoff;
	bool gso_partial;

	skb_reset_network_header(skb);
	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	if (unlikely(!pskb_may_pull(skb, sizeof(*ipv6h))))
		goto out;

	encap = SKB_GSO_CB(skb)->encap_level > 0;
	if (encap)
		features &= skb->dev->hw_enc_features;
	SKB_GSO_CB(skb)->encap_level += sizeof(*ipv6h);

	ipv6h = ipv6_hdr(skb);
	__skb_pull(skb, sizeof(*ipv6h));
	segs = ERR_PTR(-EPROTONOSUPPORT);

	proto = ipv6_gso_pull_exthdrs(skb, ipv6h->nexthdr);

	if (skb->encapsulation &&
	    skb_shinfo(skb)->gso_type & (SKB_GSO_IPXIP4 | SKB_GSO_IPXIP6))
		udpfrag = proto == IPPROTO_UDP && encap;
	else
		udpfrag = proto == IPPROTO_UDP && !skb->encapsulation;

	ops = rcu_dereference(inet6_offloads[proto]);
	if (likely(ops && ops->callbacks.gso_segment)) {
		skb_reset_transport_header(skb);
		segs = ops->callbacks.gso_segment(skb, features);
	}

	if (IS_ERR_OR_NULL(segs))
		goto out;

	gso_partial = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PARTIAL);

	for (skb = segs; skb; skb = skb->next) {
		ipv6h = (struct ipv6hdr *)(skb_mac_header(skb) + nhoff);
		if (gso_partial)
			payload_len = skb_shinfo(skb)->gso_size +
				      SKB_GSO_CB(skb)->data_offset +
				      skb->head - (unsigned char *)(ipv6h + 1);
		else
			payload_len = skb->len - nhoff - sizeof(*ipv6h);
		ipv6h->payload_len = htons(payload_len);
		skb->network_header = (u8 *)ipv6h - skb->head;

		if (udpfrag) {
			unfrag_ip6hlen = ip6_find_1stfragopt(skb, &prevhdr);
			fptr = (struct frag_hdr *)((u8 *)ipv6h + unfrag_ip6hlen);
			fptr->frag_off = htons(offset);
			if (skb->next)
				fptr->frag_off |= htons(IP6_MF);
			offset += (ntohs(ipv6h->payload_len) -
				   sizeof(struct frag_hdr));
		}
		if (encap)
			skb_reset_inner_headers(skb);
	}

out:
	return segs;
}