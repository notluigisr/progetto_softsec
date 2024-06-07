static void __perf_event_sync_stat(struct perf_event *event,
				     struct perf_event *next_event)
{
	u64 value;

	if (!event->attr.inherit_stat)
		return;

	
	if (event->state == PERF_EVENT_STATE_ACTIVE)
		event->pmu->read(event);

	perf_event_update_time(event);

	
	value = local64_read(&next_event->count);
	value = local64_xchg(&event->count, value);
	local64_set(&next_event->count, value);

	swap(event->total_time_enabled, next_event->total_time_enabled);
	swap(event->total_time_running, next_event->total_time_running);

	
	perf_event_update_userpage(event);
	perf_event_update_userpage(next_event);
}