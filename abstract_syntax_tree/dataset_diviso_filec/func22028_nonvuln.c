static void perf_duration_warn(struct irq_work *w)
{
	printk_ratelimited(KERN_WARNING
		"STR"
		"STR",
		__report_avg, __report_allowed,
		sysctl_perf_event_sample_rate);
}