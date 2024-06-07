static int tstats_show(struct seq_file *m, void *v)
{
	struct timespec64 period;
	struct entry *entry;
	unsigned long ms;
	long events = 0;
	ktime_t time;
	int i;

	mutex_lock(&show_mutex);
	
	if (timer_stats_active)
		time_stop = ktime_get();

	time = ktime_sub(time_stop, time_start);

	period = ktime_to_timespec64(time);
	ms = period.tv_nsec / 1000000;

	seq_puts(m, "STR");
	seq_printf(m, "STR", (long)period.tv_sec, ms);
	if (atomic_read(&overflow_count))
		seq_printf(m, "STR", atomic_read(&overflow_count));
	seq_printf(m, "STR");

	for (i = 0; i < nr_entries; i++) {
		entry = entries + i;
		if (entry->flags & TIMER_DEFERRABLE) {
			seq_printf(m, "STR",
				entry->count, entry->pid, entry->comm);
		} else {
			seq_printf(m, "STR",
				entry->count, entry->pid, entry->comm);
		}

		print_name_offset(m, (unsigned long)entry->start_func);
		seq_puts(m, "STR");
		print_name_offset(m, (unsigned long)entry->expire_func);
		seq_puts(m, "STR");

		events += entry->count;
	}

	ms += period.tv_sec * 1000;
	if (!ms)
		ms = 1;

	if (events && period.tv_sec)
		seq_printf(m, "STR",
			   events, events * 1000 / ms,
			   (events * 1000000 / ms) % 1000);
	else
		seq_printf(m, "STR", events);

	mutex_unlock(&show_mutex);

	return 0;
}