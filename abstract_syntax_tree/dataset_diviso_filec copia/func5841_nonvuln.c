static void perf_event_switch_output(struct perf_event *event, void *data)
{
	struct perf_switch_event *se = data;
	struct perf_output_handle handle;
	struct perf_sample_data sample;
	int ret;

	if (!perf_event_switch_match(event))
		return;

	
	if (event->ctx->task) {
		se->event_id.header.type = PERF_RECORD_SWITCH;
		se->event_id.header.size = sizeof(se->event_id.header);
	} else {
		se->event_id.header.type = PERF_RECORD_SWITCH_CPU_WIDE;
		se->event_id.header.size = sizeof(se->event_id);
		se->event_id.next_prev_pid =
					perf_event_pid(event, se->next_prev);
		se->event_id.next_prev_tid =
					perf_event_tid(event, se->next_prev);
	}

	perf_event_header__init_id(&se->event_id.header, &sample, event);

	ret = perf_output_begin(&handle, event, se->event_id.header.size);
	if (ret)
		return;

	if (event->ctx->task)
		perf_output_put(&handle, se->event_id.header);
	else
		perf_output_put(&handle, se->event_id);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
}