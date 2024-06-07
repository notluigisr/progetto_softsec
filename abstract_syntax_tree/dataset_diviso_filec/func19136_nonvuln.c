static void __exit clusterip_tg_exit(void)
{
	pr_info("STR", CLUSTERIP_VERSION);
#ifdef CONFIG_PROC_FS
	remove_proc_entry(clusterip_procdir->name, clusterip_procdir->parent);
#endif
	nf_unregister_hook(&cip_arp_ops);
	xt_unregister_target(&clusterip_tg_reg);

	
	rcu_barrier_bh();
}