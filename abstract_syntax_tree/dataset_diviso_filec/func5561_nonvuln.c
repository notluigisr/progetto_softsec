trigger_dyntick_cpu(struct timer_base *base, struct timer_list *timer)
{
	if (!is_timers_nohz_active())
		return;

	
	if (timer->flags & TIMER_DEFERRABLE) {
		if (tick_nohz_full_cpu(base->cpu))
			wake_up_nohz_cpu(base->cpu);
		return;
	}

	
	if (!base->is_idle)
		return;

	
	if (time_after_eq(timer->expires, base->next_expiry))
		return;

	
	if (time_before(timer->expires, base->clk)) {
		
		base->next_expiry = base->clk;
	} else {
		base->next_expiry = timer->expires;
	}
	wake_up_nohz_cpu(base->cpu);
}