iter_fill_rtt(struct iter_env* iter_env, struct module_env* env,
	uint8_t* name, size_t namelen, uint16_t qtype, time_t now, 
	struct delegpt* dp, int* best_rtt, struct sock_list* blacklist,
	size_t* num_suitable_results)
{
	int got_it = 0;
	struct delegpt_addr* a;
	*num_suitable_results = 0;

	if(dp->bogus)
		return 0; 
	for(a=dp->result_list; a; a = a->next_result) {
		a->sel_rtt = iter_filter_unsuitable(iter_env, env, 
			name, namelen, qtype, now, a);
		if(a->sel_rtt != -1) {
			if(sock_list_find(blacklist, &a->addr, a->addrlen))
				a->sel_rtt += BLACKLIST_PENALTY;

			if(!got_it) {
				*best_rtt = a->sel_rtt;
				got_it = 1;
			} else if(a->sel_rtt < *best_rtt) {
				*best_rtt = a->sel_rtt;
			}
			(*num_suitable_results)++;
		}
	}
	return got_it;
}