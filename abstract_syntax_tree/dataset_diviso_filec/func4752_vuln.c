static int __init sit_init(void)
{
	int err;

	printk(KERN_INFO "STR");

	if (xfrm4_tunnel_register(&sit_handler, AF_INET6) < 0) {
		printk(KERN_INFO "STR");
		return -EAGAIN;
	}

	err = register_pernet_device(&sit_net_ops);
	if (err < 0)
		xfrm4_tunnel_deregister(&sit_handler, AF_INET6);

	return err;
}