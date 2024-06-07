static void io_iopoll_complete(struct io_ring_ctx *ctx, unsigned int *nr_events,
			       struct list_head *done)
{
	struct req_batch rb;
	struct io_kiocb *req;

	
	smp_rmb();

	io_init_req_batch(&rb);
	while (!list_empty(done)) {
		int cflags = 0;

		req = list_first_entry(done, struct io_kiocb, inflight_entry);
		list_del(&req->inflight_entry);

		if (READ_ONCE(req->result) == -EAGAIN) {
			req->iopoll_completed = 0;
			if (io_rw_reissue(req))
				continue;
		}

		if (req->flags & REQ_F_BUFFER_SELECTED)
			cflags = io_put_rw_kbuf(req);

		__io_cqring_fill_event(req, req->result, cflags);
		(*nr_events)++;

		if (refcount_dec_and_test(&req->refs))
			io_req_free_batch(&rb, req, &ctx->submit_state);
	}

	io_commit_cqring(ctx);
	io_cqring_ev_posted_iopoll(ctx);
	io_req_free_batch_finish(ctx, &rb);
}