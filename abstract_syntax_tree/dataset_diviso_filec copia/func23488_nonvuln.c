ip_vs_new_dest(struct ip_vs_service *svc, struct ip_vs_dest_user_kern *udest,
	       struct ip_vs_dest **dest_p)
{
	struct ip_vs_dest *dest;
	unsigned atype;

	EnterFunction(2);

#ifdef CONFIG_IP_VS_IPV6
	if (svc->af == AF_INET6) {
		atype = ipv6_addr_type(&udest->addr.in6);
		if ((!(atype & IPV6_ADDR_UNICAST) ||
			atype & IPV6_ADDR_LINKLOCAL) &&
			!__ip_vs_addr_is_local_v6(&udest->addr.in6))
			return -EINVAL;
	} else
#endif
	{
		atype = inet_addr_type(&init_net, udest->addr.ip);
		if (atype != RTN_LOCAL && atype != RTN_UNICAST)
			return -EINVAL;
	}

	dest = kzalloc(sizeof(struct ip_vs_dest), GFP_ATOMIC);
	if (dest == NULL) {
		pr_err("STR", __func__);
		return -ENOMEM;
	}

	dest->af = svc->af;
	dest->protocol = svc->protocol;
	dest->vaddr = svc->addr;
	dest->vport = svc->port;
	dest->vfwmark = svc->fwmark;
	ip_vs_addr_copy(svc->af, &dest->addr, &udest->addr);
	dest->port = udest->port;

	atomic_set(&dest->activeconns, 0);
	atomic_set(&dest->inactconns, 0);
	atomic_set(&dest->persistconns, 0);
	atomic_set(&dest->refcnt, 0);

	INIT_LIST_HEAD(&dest->d_list);
	spin_lock_init(&dest->dst_lock);
	spin_lock_init(&dest->stats.lock);
	__ip_vs_update_dest(svc, dest, udest);
	ip_vs_new_estimator(&dest->stats);

	*dest_p = dest;

	LeaveFunction(2);
	return 0;
}