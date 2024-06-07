static void __exit ipgre_fini(void)
{
	rtnl_link_unregister(&ipgre_tap_ops);
	rtnl_link_unregister(&ipgre_link_ops);
	unregister_pernet_device(&ipgre_net_ops);
	if (inet_del_protocol(&ipgre_protocol, IPPROTO_GRE) < 0)
		printk(KERN_INFO "STR");
}