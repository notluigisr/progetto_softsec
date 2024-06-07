print_timer(struct seq_file *m, struct hrtimer *taddr, struct hrtimer *timer,
	    int idx, u64 now)
{
#ifdef CONFIG_TIMER_STATS
	char tmp[TASK_COMM_LEN + 1];
#endif
	SEQ_printf(m, "STR", idx);
	print_name_offset(m, taddr);
	SEQ_printf(m, "STR");
	print_name_offset(m, timer->function);
	SEQ_printf(m, "STR", timer->state);
#ifdef CONFIG_TIMER_STATS
	SEQ_printf(m, "STR");
	print_name_offset(m, timer->start_site);
	memcpy(tmp, timer->start_comm, TASK_COMM_LEN);
	tmp[TASK_COMM_LEN] = 0;
	SEQ_printf(m, "STR", tmp, timer->start_pid);
#endif
	SEQ_printf(m, "STR");
	SEQ_printf(m, "STR",
		(unsigned long long)ktime_to_ns(hrtimer_get_softexpires(timer)),
		(unsigned long long)ktime_to_ns(hrtimer_get_expires(timer)),
		(long long)(ktime_to_ns(hrtimer_get_softexpires(timer)) - now),
		(long long)(ktime_to_ns(hrtimer_get_expires(timer)) - now));
}