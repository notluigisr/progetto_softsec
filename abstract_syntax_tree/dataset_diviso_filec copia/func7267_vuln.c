static unsigned long wakeup_gran(struct sched_entity *se)
{
	unsigned long gran = sysctl_sched_wakeup_granularity;

	
	if (unlikely(se->load.weight > NICE_0_LOAD))
		gran = calc_delta_fair(gran, &se->load);

	return gran;
}