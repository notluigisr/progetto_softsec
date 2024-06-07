static void io_flush_timeouts(struct io_ring_ctx *ctx)
{
	u32 seq = ctx->cached_cq_tail - atomic_read(&ctx->cq_timeouts);

	while (!list_empty(&ctx->timeout_list)) {
		u32 events_needed, events_got;
		struct io_kiocb *req = list_first_entry(&ctx->timeout_list,
						struct io_kiocb, timeout.list);

		if (io_is_timeout_noseq(req))
			break;

		
		events_needed = req->timeout.target_seq - ctx->cq_last_tm_flush;
		events_got = seq - ctx->cq_last_tm_flush;
		if (events_got < events_needed)
			break;

		list_del_init(&req->timeout.list);
		io_kill_timeout(req, 0);
	}
	ctx->cq_last_tm_flush = seq;
}