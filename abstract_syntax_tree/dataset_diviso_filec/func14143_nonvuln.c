static void init_rt_rq(struct rt_rq *rt_rq, struct rq *rq)
{
	struct rt_prio_array *array;
	int i;

	array = &rt_rq->active;
	for (i = 0; i < MAX_RT_PRIO; i++) {
		INIT_LIST_HEAD(array->queue + i);
		__clear_bit(i, array->bitmap);
	}
	
	__set_bit(MAX_RT_PRIO, array->bitmap);

#if defined CONFIG_SMP || defined CONFIG_RT_GROUP_SCHED
	rt_rq->highest_prio = MAX_RT_PRIO;
#endif
#ifdef CONFIG_SMP
	rt_rq->rt_nr_migratory = 0;
	rt_rq->overloaded = 0;
#endif

	rt_rq->rt_time = 0;
	rt_rq->rt_throttled = 0;
	rt_rq->rt_runtime = 0;
	spin_lock_init(&rt_rq->rt_runtime_lock);

#ifdef CONFIG_RT_GROUP_SCHED
	rt_rq->rt_nr_boosted = 0;
	rt_rq->rq = rq;
#endif
}