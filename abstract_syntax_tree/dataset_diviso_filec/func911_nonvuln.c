static void unaccount_event(struct perf_event *event)
{
	bool dec = false;

	if (event->parent)
		return;

	if (event->attach_state & PERF_ATTACH_TASK)
		dec = true;
	if (event->attr.mmap || event->attr.mmap_data)
		atomic_dec(&nr_mmap_events);
	if (event->attr.comm)
		atomic_dec(&nr_comm_events);
	if (event->attr.task)
		atomic_dec(&nr_task_events);
	if (event->attr.freq)
		unaccount_freq_event();
	if (event->attr.context_switch) {
		dec = true;
		atomic_dec(&nr_switch_events);
	}
	if (is_cgroup_event(event))
		dec = true;
	if (has_branch_stack(event))
		dec = true;

	if (dec) {
		if (!atomic_add_unless(&perf_sched_count, -1, 1))
			schedule_delayed_work(&perf_sched_work, HZ);
	}

	unaccount_event_cpu(event, event->cpu);
}