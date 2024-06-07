static void esp6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
		     int type, int code, int offset, __be32 info)
{
	struct ipv6hdr *iph = (struct ipv6hdr*)skb->data;
	struct ip_esp_hdr *esph = (struct ip_esp_hdr *)(skb->data + offset);
	struct xfrm_state *x;

	if (type != ICMPV6_DEST_UNREACH &&
	    type != ICMPV6_PKT_TOOBIG)
		return;

	x = xfrm_state_lookup((xfrm_address_t *)&iph->daddr, esph->spi, IPPROTO_ESP, AF_INET6);
	if (!x)
		return;
	printk(KERN_DEBUG "STR",
			ntohl(esph->spi), NIP6(iph->daddr));
	xfrm_state_put(x);
}