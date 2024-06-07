			  bool poll_only)
	__must_hold(&ctx->completion_lock)
{
	struct io_kiocb *req = io_poll_find(ctx, sqe_addr, poll_only);

	if (!req)
		return -ENOENT;
	io_poll_cancel_req(req);
	return 0;