static inline void timer_stats_timer_set_start_info(struct timer_list *timer)
{
	if (likely(!timer_stats_active))
		return;
	__timer_stats_timer_set_start_info(timer, __builtin_return_address(0));
}