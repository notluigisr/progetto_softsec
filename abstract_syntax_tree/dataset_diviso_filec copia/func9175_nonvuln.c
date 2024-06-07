static int hrtimer_reprogram(struct hrtimer *timer,
			     struct hrtimer_clock_base *base)
{
	ktime_t *expires_next = &__get_cpu_var(hrtimer_bases).expires_next;
	ktime_t expires = ktime_sub(timer->expires, base->offset);
	int res;

	
	if (hrtimer_callback_running(timer))
		return 0;

	if (expires.tv64 >= expires_next->tv64)
		return 0;

	
	res = tick_program_event(expires, 0);
	if (!IS_ERR_VALUE(res))
		*expires_next = expires;
	return res;
}