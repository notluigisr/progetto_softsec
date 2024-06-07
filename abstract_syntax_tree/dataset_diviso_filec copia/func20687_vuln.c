static inline void timer_stats_account_hrtimer(struct hrtimer *timer)
{
#ifdef CONFIG_TIMER_STATS
	if (likely(!timer_stats_active))
		return;
	timer_stats_update_stats(timer, timer->start_pid, timer->start_site,
				 timer->function, timer->start_comm, 0);
#endif
}