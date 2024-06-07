static int __net_init inet6_net_init(struct net *net)
{
	int err = 0;

	net->ipv6.sysctl.bindv6only = 0;
	net->ipv6.sysctl.icmpv6_time = 1*HZ;
	atomic_set(&net->ipv6.rt_genid, 0);

	err = ipv6_init_mibs(net);
	if (err)
		return err;
#ifdef CONFIG_PROC_FS
	err = udp6_proc_init(net);
	if (err)
		goto out;
	err = tcp6_proc_init(net);
	if (err)
		goto proc_tcp6_fail;
	err = ac6_proc_init(net);
	if (err)
		goto proc_ac6_fail;
#endif
	return err;

#ifdef CONFIG_PROC_FS
proc_ac6_fail:
	tcp6_proc_exit(net);
proc_tcp6_fail:
	udp6_proc_exit(net);
out:
	ipv6_cleanup_mibs(net);
	return err;
#endif
}