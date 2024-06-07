place_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int initial)
{
	u64 vruntime;

	if (first_fair(cfs_rq)) {
		vruntime = min_vruntime(cfs_rq->min_vruntime,
				__pick_next_entity(cfs_rq)->vruntime);
	} else
		vruntime = cfs_rq->min_vruntime;

	
	if (initial && sched_feat(START_DEBIT))
		vruntime += sched_vslice_add(cfs_rq, se);

	if (!initial) {
		
		if (sched_feat(NEW_FAIR_SLEEPERS)) {
			if (sched_feat(NORMALIZED_SLEEPER))
				vruntime -= calc_delta_fair(sysctl_sched_latency,
						&cfs_rq->load);
			else
				vruntime -= sysctl_sched_latency;
		}

		
		vruntime = max_vruntime(se->vruntime, vruntime);
	}

	se->vruntime = vruntime;
}