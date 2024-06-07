static __exit void sctp_exit(void)
{
	

	
	sctp_v6_del_protocol();
	sctp_v4_del_protocol();

	unregister_pernet_subsys(&sctp_net_ops);

	
	sctp_v6_protosw_exit();
	sctp_v4_protosw_exit();

	
	sctp_v6_pf_exit();
	sctp_v4_pf_exit();

	sctp_sysctl_unregister();

	free_pages((unsigned long)sctp_assoc_hashtable,
		   get_order(sctp_assoc_hashsize *
			     sizeof(struct sctp_hashbucket)));
	kfree(sctp_ep_hashtable);
	free_pages((unsigned long)sctp_port_hashtable,
		   get_order(sctp_port_hashsize *
			     sizeof(struct sctp_bind_hashbucket)));

	percpu_counter_destroy(&sctp_sockets_allocated);

	rcu_barrier(); 

	kmem_cache_destroy(sctp_chunk_cachep);
	kmem_cache_destroy(sctp_bucket_cachep);
}