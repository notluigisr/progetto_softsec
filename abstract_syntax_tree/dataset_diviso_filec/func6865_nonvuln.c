int __init fib6_init(void)
{
	int ret = -ENOMEM;

	fib6_node_kmem = kmem_cache_create("STR",
					   sizeof(struct fib6_node),
					   0, SLAB_HWCACHE_ALIGN,
					   NULL);
	if (!fib6_node_kmem)
		goto out;

	ret = register_pernet_subsys(&fib6_net_ops);
	if (ret)
		goto out_kmem_cache_create;

	ret = __rtnl_register(PF_INET6, RTM_GETROUTE, NULL, inet6_dump_fib,
			      NULL);
	if (ret)
		goto out_unregister_subsys;
out:
	return ret;

out_unregister_subsys:
	unregister_pernet_subsys(&fib6_net_ops);
out_kmem_cache_create:
	kmem_cache_destroy(fib6_node_kmem);
	goto out;
}