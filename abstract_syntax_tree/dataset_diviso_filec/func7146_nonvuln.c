static void io_iopoll_req_issued(struct io_kiocb *req)
{
	struct io_ring_ctx *ctx = req->ctx;

	
	if (list_empty(&ctx->poll_list)) {
		ctx->poll_multi_file = false;
	} else if (!ctx->poll_multi_file) {
		struct io_kiocb *list_req;

		list_req = list_first_entry(&ctx->poll_list, struct io_kiocb,
						list);
		if (list_req->rw.ki_filp != req->rw.ki_filp)
			ctx->poll_multi_file = true;
	}

	
	if (req->flags & REQ_F_IOPOLL_COMPLETED)
		list_add(&req->list, &ctx->poll_list);
	else
		list_add_tail(&req->list, &ctx->poll_list);
}