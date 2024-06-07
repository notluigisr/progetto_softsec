static inline void sched_init_granularity(void)
{
	unsigned int factor = 1 + ilog2(num_online_cpus());
	const unsigned long limit = 200000000;

	sysctl_sched_min_granularity *= factor;
	if (sysctl_sched_min_granularity > limit)
		sysctl_sched_min_granularity = limit;

	sysctl_sched_latency *= factor;
	if (sysctl_sched_latency > limit)
		sysctl_sched_latency = limit;

	sysctl_sched_wakeup_granularity *= factor;
}