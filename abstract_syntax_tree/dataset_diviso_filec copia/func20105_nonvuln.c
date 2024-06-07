void clear_sched_clock_stable(void)
{
	__sched_clock_stable_early = 0;

	smp_mb(); 

	if (!sched_clock_running)
		return;

	schedule_work(&sched_clock_work);
}