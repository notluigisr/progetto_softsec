static void __net_exit nfnetlink_net_exit_batch(struct list_head *net_exit_list)
{
	struct net *net;

	list_for_each_entry(net, net_exit_list, exit_list)
		RCU_INIT_POINTER(net->nfnl, NULL);
	synchronize_net();
	list_for_each_entry(net, net_exit_list, exit_list)
		netlink_kernel_release(net->nfnl_stash);
}