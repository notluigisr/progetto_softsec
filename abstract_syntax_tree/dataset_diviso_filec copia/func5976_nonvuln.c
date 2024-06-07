static struct dst_entry *vxlan6_get_route(struct vxlan_dev *vxlan,
					  struct net_device *dev,
					  struct vxlan_sock *sock6,
					  struct sk_buff *skb, int oif, u8 tos,
					  __be32 label,
					  const struct in6_addr *daddr,
					  struct in6_addr *saddr,
					  __be16 dport, __be16 sport,
					  struct dst_cache *dst_cache,
					  const struct ip_tunnel_info *info)
{
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	struct dst_entry *ndst;
	struct flowi6 fl6;

	if (!sock6)
		return ERR_PTR(-EIO);

	if (tos && !info)
		use_cache = false;
	if (use_cache) {
		ndst = dst_cache_get_ip6(dst_cache, saddr);
		if (ndst)
			return ndst;
	}

	memset(&fl6, 0, sizeof(fl6));
	fl6.flowi6_oif = oif;
	fl6.daddr = *daddr;
	fl6.saddr = *saddr;
	fl6.flowlabel = ip6_make_flowinfo(RT_TOS(tos), label);
	fl6.flowi6_mark = skb->mark;
	fl6.flowi6_proto = IPPROTO_UDP;
	fl6.fl6_dport = dport;
	fl6.fl6_sport = sport;

	ndst = ipv6_stub->ipv6_dst_lookup_flow(vxlan->net, sock6->sock->sk,
					       &fl6, NULL);
	if (unlikely(IS_ERR(ndst))) {
		netdev_dbg(dev, "STR", daddr);
		return ERR_PTR(-ENETUNREACH);
	}

	if (unlikely(ndst->dev == dev)) {
		netdev_dbg(dev, "STR", daddr);
		dst_release(ndst);
		return ERR_PTR(-ELOOP);
	}

	*saddr = fl6.saddr;
	if (use_cache)
		dst_cache_set_ip6(dst_cache, ndst, saddr);
	return ndst;
}