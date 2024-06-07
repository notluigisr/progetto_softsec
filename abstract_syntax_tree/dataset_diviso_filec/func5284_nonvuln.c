void timer_clear_idle(void)
{
	struct timer_base *base = this_cpu_ptr(&timer_bases[BASE_STD]);

	
	base->is_idle = false;
}