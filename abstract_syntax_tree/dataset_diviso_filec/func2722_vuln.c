static int hhf_init(struct Qdisc *sch, struct nlattr *opt,
		    struct netlink_ext_ack *extack)
{
	struct hhf_sched_data *q = qdisc_priv(sch);
	int i;

	sch->limit = 1000;
	q->quantum = psched_mtu(qdisc_dev(sch));
	q->perturbation = prandom_u32();
	INIT_LIST_HEAD(&q->new_buckets);
	INIT_LIST_HEAD(&q->old_buckets);

	
	q->hhf_reset_timeout = HZ / 25; 
	q->hhf_admit_bytes = 131072;    
	q->hhf_evict_timeout = HZ;      
	q->hhf_non_hh_weight = 2;

	if (opt) {
		int err = hhf_change(sch, opt, extack);

		if (err)
			return err;
	}

	if (!q->hh_flows) {
		
		q->hh_flows = kvcalloc(HH_FLOWS_CNT, sizeof(struct list_head),
				       GFP_KERNEL);
		if (!q->hh_flows)
			return -ENOMEM;
		for (i = 0; i < HH_FLOWS_CNT; i++)
			INIT_LIST_HEAD(&q->hh_flows[i]);

		
		q->hh_flows_limit = 2 * HH_FLOWS_CNT;
		q->hh_flows_overlimit = 0;
		q->hh_flows_total_cnt = 0;
		q->hh_flows_current_cnt = 0;

		
		for (i = 0; i < HHF_ARRAYS_CNT; i++) {
			q->hhf_arrays[i] = kvcalloc(HHF_ARRAYS_LEN,
						    sizeof(u32),
						    GFP_KERNEL);
			if (!q->hhf_arrays[i]) {
				
				return -ENOMEM;
			}
		}
		q->hhf_arrays_reset_timestamp = hhf_time_stamp();

		
		for (i = 0; i < HHF_ARRAYS_CNT; i++) {
			q->hhf_valid_bits[i] = kvzalloc(HHF_ARRAYS_LEN /
							  BITS_PER_BYTE, GFP_KERNEL);
			if (!q->hhf_valid_bits[i]) {
				
				return -ENOMEM;
			}
		}

		
		for (i = 0; i < WDRR_BUCKET_CNT; i++) {
			struct wdrr_bucket *bucket = q->buckets + i;

			INIT_LIST_HEAD(&bucket->bucketchain);
		}
	}

	return 0;
}