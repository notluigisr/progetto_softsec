static void __perf_event_read(void *info)
{
	struct perf_event *event = info;
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);

	
	if (ctx->task && cpuctx->task_ctx != ctx)
		return;

	raw_spin_lock(&ctx->lock);
	if (ctx->is_active) {
		update_context_time(ctx);
		update_cgrp_time_from_event(event);
	}
	update_event_times(event);
	if (event->state == PERF_EVENT_STATE_ACTIVE)
		event->pmu->read(event);
	raw_spin_unlock(&ctx->lock);
}