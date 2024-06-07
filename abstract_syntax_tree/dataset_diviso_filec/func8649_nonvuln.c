perf_install_in_context(struct perf_event_context *ctx,
			struct perf_event *event,
			int cpu)
{
	struct task_struct *task = READ_ONCE(ctx->task);

	lockdep_assert_held(&ctx->mutex);

	event->ctx = ctx;
	if (event->cpu != -1)
		event->cpu = cpu;

	if (!task) {
		cpu_function_call(cpu, __perf_install_in_context, event);
		return;
	}

	
	if (WARN_ON_ONCE(task == TASK_TOMBSTONE))
		return;

	
again:
	
	if (!cpu_function_call(task_cpu(task), __perf_install_in_context, event))
		return;

	raw_spin_lock_irq(&ctx->lock);
	task = ctx->task;
	if (WARN_ON_ONCE(task == TASK_TOMBSTONE)) {
		
		raw_spin_unlock_irq(&ctx->lock);
		return;
	}
	raw_spin_unlock_irq(&ctx->lock);
	
	goto again;
}