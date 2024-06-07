static int ip_vs_stats_percpu_show(struct seq_file *seq, void *v)
{
	struct net *net = seq_file_single_net(seq);
	struct ip_vs_stats *tot_stats = &net_ipvs(net)->tot_stats;
	struct ip_vs_cpu_stats *cpustats = tot_stats->cpustats;
	struct ip_vs_stats_user rates;
	int i;


	seq_puts(seq,
		 "STR");
	seq_printf(seq,
		   "STR");

	for_each_possible_cpu(i) {
		struct ip_vs_cpu_stats *u = per_cpu_ptr(cpustats, i);
		unsigned int start;
		__u64 inbytes, outbytes;

		do {
			start = u64_stats_fetch_begin_bh(&u->syncp);
			inbytes = u->ustats.inbytes;
			outbytes = u->ustats.outbytes;
		} while (u64_stats_fetch_retry_bh(&u->syncp, start));

		seq_printf(seq, "STR",
			   i, u->ustats.conns, u->ustats.inpkts,
			   u->ustats.outpkts, (__u64)inbytes,
			   (__u64)outbytes);
	}

	spin_lock_bh(&tot_stats->lock);

	seq_printf(seq, "STR",
		   tot_stats->ustats.conns, tot_stats->ustats.inpkts,
		   tot_stats->ustats.outpkts,
		   (unsigned long long) tot_stats->ustats.inbytes,
		   (unsigned long long) tot_stats->ustats.outbytes);

	ip_vs_read_estimator(&rates, tot_stats);

	spin_unlock_bh(&tot_stats->lock);


	seq_puts(seq,
		   "STR");
	seq_printf(seq, "STR",
			rates.cps,
			rates.inpps,
			rates.outpps,
			rates.inbps,
			rates.outbps);

	return 0;
}