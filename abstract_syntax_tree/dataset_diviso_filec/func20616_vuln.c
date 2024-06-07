 */
static struct sk_buff *napi_frags_skb(struct napi_struct *napi)
{
	struct sk_buff *skb = napi->skb;
	const struct ethhdr *eth;
	unsigned int hlen = sizeof(*eth);

	napi->skb = NULL;

	skb_reset_mac_header(skb);
	skb_gro_reset_offset(skb);

	eth = skb_gro_header_fast(skb, 0);
	if (unlikely(skb_gro_header_hard(skb, hlen))) {
		eth = skb_gro_header_slow(skb, hlen, 0);
		if (unlikely(!eth)) {
			net_warn_ratelimited("STR",
					     __func__, napi->dev->name);
			napi_reuse_skb(napi, skb);
			return NULL;
		}
	} else {
		gro_pull_from_frag0(skb, hlen);
		NAPI_GRO_CB(skb)->frag0 += hlen;
		NAPI_GRO_CB(skb)->frag0_len -= hlen;
	}
	__skb_pull(skb, hlen);

	
	skb->protocol = eth->h_proto;

	return skb;