static void __exit esp6_fini(void)
{
	if (inet6_del_protocol(&esp6_protocol, IPPROTO_ESP) < 0)
		printk(KERN_INFO "STR");
	if (xfrm_unregister_type(&esp6_type, AF_INET6) < 0)
		printk(KERN_INFO "STR");
}