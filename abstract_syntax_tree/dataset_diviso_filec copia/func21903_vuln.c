static struct net_device *inet6_fib_lookup_dev(struct net *net,
					       const void *addr)
{
	struct net_device *dev;
	struct dst_entry *dst;
	struct flowi6 fl6;
	int err;

	if (!ipv6_stub)
		return ERR_PTR(-EAFNOSUPPORT);

	memset(&fl6, 0, sizeof(fl6));
	memcpy(&fl6.daddr, addr, sizeof(struct in6_addr));
	err = ipv6_stub->ipv6_dst_lookup(net, NULL, &dst, &fl6);
	if (err)
		return ERR_PTR(err);

	dev = dst->dev;
	dev_hold(dev);
	dst_release(dst);

	return dev;
}