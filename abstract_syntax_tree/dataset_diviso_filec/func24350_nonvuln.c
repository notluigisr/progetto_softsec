static void ipv6_del_addr(struct inet6_ifaddr *ifp)
{
	int state;
	enum cleanup_prefix_rt_t action = CLEANUP_PREFIX_RT_NOP;
	unsigned long expires;

	ASSERT_RTNL();

	spin_lock_bh(&ifp->state_lock);
	state = ifp->state;
	ifp->state = INET6_IFADDR_STATE_DEAD;
	spin_unlock_bh(&ifp->state_lock);

	if (state == INET6_IFADDR_STATE_DEAD)
		goto out;

	spin_lock_bh(&addrconf_hash_lock);
	hlist_del_init_rcu(&ifp->addr_lst);
	spin_unlock_bh(&addrconf_hash_lock);

	write_lock_bh(&ifp->idev->lock);

	if (ifp->flags&IFA_F_TEMPORARY) {
		list_del(&ifp->tmp_list);
		if (ifp->ifpub) {
			in6_ifa_put(ifp->ifpub);
			ifp->ifpub = NULL;
		}
		__in6_ifa_put(ifp);
	}

	if (ifp->flags & IFA_F_PERMANENT && !(ifp->flags & IFA_F_NOPREFIXROUTE))
		action = check_cleanup_prefix_route(ifp, &expires);

	list_del_init(&ifp->if_list);
	__in6_ifa_put(ifp);

	write_unlock_bh(&ifp->idev->lock);

	addrconf_del_dad_work(ifp);

	ipv6_ifa_notify(RTM_DELADDR, ifp);

	inet6addr_notifier_call_chain(NETDEV_DOWN, ifp);

	if (action != CLEANUP_PREFIX_RT_NOP) {
		cleanup_prefix_route(ifp, expires,
			action == CLEANUP_PREFIX_RT_DEL);
	}

	
	rt6_remove_prefsrc(ifp);
out:
	in6_ifa_put(ifp);
}