void igmp6_cleanup(void)
{
	unregister_pernet_subsys(&igmp6_net_ops);
	destroy_workqueue(mld_wq);
}