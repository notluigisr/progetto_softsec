static struct dst_entry *geneve_get_v6_dst(struct sk_buff *skb,
					   struct net_device *dev,
					   struct geneve_sock *gs6,
					   struct flowi6 *fl6,
					   const struct ip_tunnel_info *info)
{
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	struct geneve_dev *geneve = netdev_priv(dev);
	struct dst_entry *dst = NULL;
	struct dst_cache *dst_cache;
	__u8 prio;

	if (!gs6)
		return ERR_PTR(-EIO);

	memset(fl6, 0, sizeof(*fl6));
	fl6->flowi6_mark = skb->mark;
	fl6->flowi6_proto = IPPROTO_UDP;
	fl6->daddr = info->key.u.ipv6.dst;
	fl6->saddr = info->key.u.ipv6.src;
	prio = info->key.tos;
	if ((prio == 1) && !geneve->collect_md) {
		prio = ip_tunnel_get_dsfield(ip_hdr(skb), skb);
		use_cache = false;
	}

	fl6->flowlabel = ip6_make_flowinfo(RT_TOS(prio),
					   info->key.label);
	dst_cache = (struct dst_cache *)&info->dst_cache;
	if (use_cache) {
		dst = dst_cache_get_ip6(dst_cache, &fl6->saddr);
		if (dst)
			return dst;
	}
	if (ipv6_stub->ipv6_dst_lookup(geneve->net, gs6->sock->sk, &dst, fl6)) {
		netdev_dbg(dev, "STR", &fl6->daddr);
		return ERR_PTR(-ENETUNREACH);
	}
	if (dst->dev == dev) { 
		netdev_dbg(dev, "STR", &fl6->daddr);
		dst_release(dst);
		return ERR_PTR(-ELOOP);
	}

	if (use_cache)
		dst_cache_set_ip6(dst_cache, dst, &fl6->saddr);
	return dst;
}