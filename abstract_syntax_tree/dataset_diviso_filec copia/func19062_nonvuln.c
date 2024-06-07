int ipv6_sock_mc_join(struct sock *sk, int ifindex, const struct in6_addr *addr)
{
	return __ipv6_sock_mc_join(sk, ifindex, addr, MCAST_EXCLUDE);
}