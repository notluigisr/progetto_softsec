static struct dst_entry *rxe_find_route6(struct net_device *ndev,
					 struct in6_addr *saddr,
					 struct in6_addr *daddr)
{
	struct dst_entry *ndst;
	struct flowi6 fl6 = { { 0 } };

	memset(&fl6, 0, sizeof(fl6));
	fl6.flowi6_oif = ndev->ifindex;
	memcpy(&fl6.saddr, saddr, sizeof(*saddr));
	memcpy(&fl6.daddr, daddr, sizeof(*daddr));
	fl6.flowi6_proto = IPPROTO_UDP;

	if (unlikely(ipv6_stub->ipv6_dst_lookup(sock_net(recv_sockets.sk6->sk),
						recv_sockets.sk6->sk, &ndst, &fl6))) {
		pr_err_ratelimited("STR", daddr);
		goto put;
	}

	if (unlikely(ndst->error)) {
		pr_err("STR", daddr);
		goto put;
	}

	return ndst;
put:
	dst_release(ndst);
	return NULL;
}