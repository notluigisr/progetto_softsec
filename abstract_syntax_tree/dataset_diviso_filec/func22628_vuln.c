static int __init xfrm6_tunnel_init(void)
{
	int rv;

	rv = xfrm_register_type(&xfrm6_tunnel_type, AF_INET6);
	if (rv < 0)
		goto err;
	rv = xfrm6_tunnel_register(&xfrm6_tunnel_handler, AF_INET6);
	if (rv < 0)
		goto unreg;
	rv = xfrm6_tunnel_register(&xfrm46_tunnel_handler, AF_INET);
	if (rv < 0)
		goto dereg6;
	rv = xfrm6_tunnel_spi_init();
	if (rv < 0)
		goto dereg46;
	rv = register_pernet_subsys(&xfrm6_tunnel_net_ops);
	if (rv < 0)
		goto deregspi;
	return 0;

deregspi:
	xfrm6_tunnel_spi_fini();
dereg46:
	xfrm6_tunnel_deregister(&xfrm46_tunnel_handler, AF_INET);
dereg6:
	xfrm6_tunnel_deregister(&xfrm6_tunnel_handler, AF_INET6);
unreg:
	xfrm_unregister_type(&xfrm6_tunnel_type, AF_INET6);
err:
	return rv;
}