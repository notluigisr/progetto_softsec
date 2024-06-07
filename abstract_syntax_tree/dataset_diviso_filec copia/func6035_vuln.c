static inline void timer_stats_timer_clear_start_info(struct timer_list *timer)
{
	timer->start_site = NULL;
}