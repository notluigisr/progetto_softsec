static int fib_netdev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct netdev_notifier_changeupper_info *info;
	struct in_device *in_dev;
	struct net *net = dev_net(dev);
	unsigned int flags;

	if (event == NETDEV_UNREGISTER) {
		fib_disable_ip(dev, event, true);
		rt_flush_dev(dev);
		return NOTIFY_DONE;
	}

	in_dev = __in_dev_get_rtnl(dev);
	if (!in_dev)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		for_ifa(in_dev) {
			fib_add_ifaddr(ifa);
		} endfor_ifa(in_dev);
#ifdef CONFIG_IP_ROUTE_MULTIPATH
		fib_sync_up(dev, RTNH_F_DEAD);
#endif
		atomic_inc(&net->ipv4.dev_addr_genid);
		rt_cache_flush(net);
		break;
	case NETDEV_DOWN:
		fib_disable_ip(dev, event, false);
		break;
	case NETDEV_CHANGE:
		flags = dev_get_flags(dev);
		if (flags & (IFF_RUNNING | IFF_LOWER_UP))
			fib_sync_up(dev, RTNH_F_LINKDOWN);
		else
			fib_sync_down_dev(dev, event, false);
		
	case NETDEV_CHANGEMTU:
		rt_cache_flush(net);
		break;
	case NETDEV_CHANGEUPPER:
		info = ptr;
		
		if (info->upper_dev && netif_is_l3_master(info->upper_dev))
			fib_disable_ip(dev, NETDEV_DOWN, true);
		break;
	}
	return NOTIFY_DONE;
}