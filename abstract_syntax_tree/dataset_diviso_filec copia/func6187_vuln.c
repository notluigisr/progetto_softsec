static void timer_stats_account_timer(struct timer_list *timer)
{
	void *site;

	
	site = READ_ONCE(timer->start_site);
	if (likely(!site))
		return;

	timer_stats_update_stats(timer, timer->start_pid, site,
				 timer->function, timer->start_comm,
				 timer->flags);
}