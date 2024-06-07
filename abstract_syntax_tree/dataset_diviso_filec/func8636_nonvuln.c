ctx_event_to_rotate(struct perf_event_context *ctx)
{
	struct perf_event *event;

	
	event = list_first_entry_or_null(&ctx->flexible_active,
					 struct perf_event, active_list);

	
	if (!event) {
		event = rb_entry_safe(rb_first(&ctx->flexible_groups.tree),
				      typeof(*event), group_node);
	}

	
	ctx->rotate_necessary = 0;

	return event;
}