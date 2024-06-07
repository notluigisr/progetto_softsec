void __init tcp_init(void)
{
	int max_rshare, max_wshare, cnt;
	unsigned long limit;
	unsigned int i;

	BUILD_BUG_ON(sizeof(struct tcp_skb_cb) >
		     FIELD_SIZEOF(struct sk_buff, cb));

	percpu_counter_init(&tcp_sockets_allocated, 0, GFP_KERNEL);
	percpu_counter_init(&tcp_orphan_count, 0, GFP_KERNEL);
	inet_hashinfo_init(&tcp_hashinfo);
	inet_hashinfo2_init(&tcp_hashinfo, "STR",
			    thash_entries, 21,  
			    0, 64 * 1024);
	tcp_hashinfo.bind_bucket_cachep =
		kmem_cache_create("STR",
				  sizeof(struct inet_bind_bucket), 0,
				  SLAB_HWCACHE_ALIGN|SLAB_PANIC, NULL);

	
	tcp_hashinfo.ehash =
		alloc_large_system_hash("STR",
					sizeof(struct inet_ehash_bucket),
					thash_entries,
					17, 
					0,
					NULL,
					&tcp_hashinfo.ehash_mask,
					0,
					thash_entries ? 0 : 512 * 1024);
	for (i = 0; i <= tcp_hashinfo.ehash_mask; i++)
		INIT_HLIST_NULLS_HEAD(&tcp_hashinfo.ehash[i].chain, i);

	if (inet_ehash_locks_alloc(&tcp_hashinfo))
		panic("STR");
	tcp_hashinfo.bhash =
		alloc_large_system_hash("STR",
					sizeof(struct inet_bind_hashbucket),
					tcp_hashinfo.ehash_mask + 1,
					17, 
					0,
					&tcp_hashinfo.bhash_size,
					NULL,
					0,
					64 * 1024);
	tcp_hashinfo.bhash_size = 1U << tcp_hashinfo.bhash_size;
	for (i = 0; i < tcp_hashinfo.bhash_size; i++) {
		spin_lock_init(&tcp_hashinfo.bhash[i].lock);
		INIT_HLIST_HEAD(&tcp_hashinfo.bhash[i].chain);
	}


	cnt = tcp_hashinfo.ehash_mask + 1;
	sysctl_tcp_max_orphans = cnt / 2;

	tcp_init_mem();
	
	limit = nr_free_buffer_pages() << (PAGE_SHIFT - 7);
	max_wshare = min(4UL*1024*1024, limit);
	max_rshare = min(6UL*1024*1024, limit);

	init_net.ipv4.sysctl_tcp_wmem[0] = SK_MEM_QUANTUM;
	init_net.ipv4.sysctl_tcp_wmem[1] = 16*1024;
	init_net.ipv4.sysctl_tcp_wmem[2] = max(64*1024, max_wshare);

	init_net.ipv4.sysctl_tcp_rmem[0] = SK_MEM_QUANTUM;
	init_net.ipv4.sysctl_tcp_rmem[1] = 131072;
	init_net.ipv4.sysctl_tcp_rmem[2] = max(131072, max_rshare);

	pr_info("STR",
		tcp_hashinfo.ehash_mask + 1, tcp_hashinfo.bhash_size);

	tcp_v4_init();
	tcp_metrics_init();
	BUG_ON(tcp_register_congestion_control(&tcp_reno) != 0);
	tcp_tasklet_init();
}