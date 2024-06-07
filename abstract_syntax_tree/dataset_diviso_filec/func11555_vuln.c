static struct net *get_target_net(struct sk_buff *skb, int netnsid)
{
	struct net *net;

	net = get_net_ns_by_id(sock_net(skb->sk), netnsid);
	if (!net)
		return ERR_PTR(-EINVAL);

	
	if (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN)) {
		put_net(net);
		return ERR_PTR(-EACCES);
	}
	return net;
}