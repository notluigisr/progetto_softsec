static inline void timer_stats_hrtimer_set_start_info(struct hrtimer *timer)
{
#ifdef CONFIG_TIMER_STATS
	if (timer->start_site)
		return;
	timer->start_site = __builtin_return_address(0);
	memcpy(timer->start_comm, current->comm, TASK_COMM_LEN);
	timer->start_pid = current->pid;
#endif
}