static int dn_nl_dump_ifaddr(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	int idx, dn_idx = 0, skip_ndevs, skip_naddr;
	struct net_device *dev;
	struct dn_dev *dn_db;
	struct dn_ifaddr *ifa;

	if (!net_eq(net, &init_net))
		return 0;

	skip_ndevs = cb->args[0];
	skip_naddr = cb->args[1];

	idx = 0;
	rcu_read_lock();
	for_each_netdev_rcu(&init_net, dev) {
		if (idx < skip_ndevs)
			goto cont;
		else if (idx > skip_ndevs) {
			
			skip_naddr = 0;
		}

		if ((dn_db = rcu_dereference(dev->dn_ptr)) == NULL)
			goto cont;

		for (ifa = rcu_dereference(dn_db->ifa_list), dn_idx = 0; ifa;
		     ifa = rcu_dereference(ifa->ifa_next), dn_idx++) {
			if (dn_idx < skip_naddr)
				continue;

			if (dn_nl_fill_ifaddr(skb, ifa, NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq, RTM_NEWADDR,
					      NLM_F_MULTI) < 0)
				goto done;
		}
cont:
		idx++;
	}
done:
	rcu_read_unlock();
	cb->args[0] = idx;
	cb->args[1] = dn_idx;

	return skb->len;
}