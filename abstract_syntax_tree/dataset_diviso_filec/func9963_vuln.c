static struct net_device *inet6_fib_lookup_dev(struct net *net,
					       const void *addr)
{
	return ERR_PTR(-EAFNOSUPPORT);
}