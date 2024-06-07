static bool ipv6_raw_deliver(struct sk_buff *skb, int nexthdr)
{
	const struct in6_addr *saddr;
	const struct in6_addr *daddr;
	struct sock *sk;
	bool delivered = false;
	__u8 hash;
	struct net *net;

	saddr = &ipv6_hdr(skb)->saddr;
	daddr = saddr + 1;

	hash = nexthdr & (RAW_HTABLE_SIZE - 1);

	read_lock(&raw_v6_hashinfo.lock);
	sk = sk_head(&raw_v6_hashinfo.ht[hash]);

	if (!sk)
		goto out;

	net = dev_net(skb->dev);
	sk = __raw_v6_lookup(net, sk, nexthdr, daddr, saddr, inet6_iif(skb));

	while (sk) {
		int filtered;

		delivered = true;
		switch (nexthdr) {
		case IPPROTO_ICMPV6:
			filtered = icmpv6_filter(sk, skb);
			break;

#if IS_ENABLED(CONFIG_IPV6_MIP6)
		case IPPROTO_MH:
		{
			
			mh_filter_t *filter;

			filter = rcu_dereference(mh_filter);
			filtered = filter ? (*filter)(sk, skb) : 0;
			break;
		}
#endif
		default:
			filtered = 0;
			break;
		}

		if (filtered < 0)
			break;
		if (filtered == 0) {
			struct sk_buff *clone = skb_clone(skb, GFP_ATOMIC);

			
			if (clone) {
				nf_reset(clone);
				rawv6_rcv(sk, clone);
			}
		}
		sk = __raw_v6_lookup(net, sk_next(sk), nexthdr, daddr, saddr,
				     inet6_iif(skb));
	}
out:
	read_unlock(&raw_v6_hashinfo.lock);
	return delivered;
}