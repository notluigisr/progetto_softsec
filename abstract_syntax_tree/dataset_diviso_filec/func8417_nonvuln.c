place_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int initial)
{
	u64 vruntime;

	if (first_fair(cfs_rq)) {
		vruntime = min_vruntime(cfs_rq->min_vruntime,
				__pick_next_entity(cfs_rq)->vruntime);
	} else
		vruntime = cfs_rq->min_vruntime;

	if (sched_feat(TREE_AVG)) {
		struct sched_entity *last = __pick_last_entity(cfs_rq);
		if (last) {
			vruntime += last->vruntime;
			vruntime >>= 1;
		}
	} else if (sched_feat(APPROX_AVG) && cfs_rq->nr_running)
		vruntime += sched_vslice(cfs_rq)/2;

	
	if (initial && sched_feat(START_DEBIT))
		vruntime += sched_vslice_add(cfs_rq, se);

	if (!initial) {
		
		if (sched_feat(NEW_FAIR_SLEEPERS)) {
			vruntime -= calc_delta_fair(sysctl_sched_latency,
						    &cfs_rq->load);
		}

		
		vruntime = max_vruntime(se->vruntime, vruntime);
	}

	se->vruntime = vruntime;
}