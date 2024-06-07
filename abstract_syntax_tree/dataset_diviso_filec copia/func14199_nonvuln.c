static void io_flush_timeouts(struct io_ring_ctx *ctx)
{
	while (!list_empty(&ctx->timeout_list)) {
		struct io_kiocb *req = list_first_entry(&ctx->timeout_list,
						struct io_kiocb, timeout.list);

		if (io_is_timeout_noseq(req))
			break;
		if (req->timeout.target_seq != ctx->cached_cq_tail
					- atomic_read(&ctx->cq_timeouts))
			break;

		list_del_init(&req->timeout.list);
		io_kill_timeout(req);
	}
}