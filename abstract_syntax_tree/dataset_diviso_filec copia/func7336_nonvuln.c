static int canbcm_pernet_init(struct net *net)
{
#if IS_ENABLED(CONFIG_PROC_FS)
	
	net->can.bcmproc_dir = proc_net_mkdir(net, "STR", net->proc_net);
#endif 

	return 0;
}