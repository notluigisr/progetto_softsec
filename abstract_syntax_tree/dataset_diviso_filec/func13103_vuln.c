static void __exit inet6_exit(void)
{
	if (disable_ipv6_mod)
		return;

	
	sock_unregister(PF_INET6);
	
	rtnl_unregister_all(PF_INET6);

	udpv6_exit();
	udplitev6_exit();
	tcpv6_exit();

	
	ipv6_packet_cleanup();
	ipv6_frag_exit();
	ipv6_exthdrs_exit();
	addrconf_cleanup();
	ip6_flowlabel_cleanup();
	ip6_route_cleanup();
#ifdef CONFIG_PROC_FS

	
	if6_proc_exit();
	ipv6_misc_proc_exit();
	udplite6_proc_exit();
	raw6_proc_exit();
#endif
	ipv6_netfilter_fini();
	igmp6_cleanup();
	ndisc_cleanup();
	ip6_mr_cleanup();
	icmpv6_cleanup();
	rawv6_exit();

	unregister_pernet_subsys(&inet6_net_ops);
	proto_unregister(&rawv6_prot);
	proto_unregister(&udplitev6_prot);
	proto_unregister(&udpv6_prot);
	proto_unregister(&tcpv6_prot);

	rcu_barrier(); 
}