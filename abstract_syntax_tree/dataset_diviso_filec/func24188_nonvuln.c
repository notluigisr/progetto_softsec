static inline void update_load_avg(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{
	u64 now = cfs_rq_clock_task(cfs_rq);
	struct rq *rq = rq_of(cfs_rq);
	int cpu = cpu_of(rq);
	int decayed;

	
	if (se->avg.last_update_time && !(flags & SKIP_AGE_LOAD))
		__update_load_avg_se(now, cpu, cfs_rq, se);

	decayed  = update_cfs_rq_load_avg(now, cfs_rq);
	decayed |= propagate_entity_load_avg(se);

	if (!se->avg.last_update_time && (flags & DO_ATTACH)) {

		
		attach_entity_load_avg(cfs_rq, se, SCHED_CPUFREQ_MIGRATION);
		update_tg_load_avg(cfs_rq, 0);

	} else if (decayed && (flags & UPDATE_TG))
		update_tg_load_avg(cfs_rq, 0);
}