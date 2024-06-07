
static int io_async_cancel(struct io_kiocb *req, unsigned int issue_flags)
{
	struct io_cancel_data cd = {
		.ctx	= req->ctx,
		.data	= req->cancel.addr,
		.flags	= req->cancel.flags,
		.seq	= atomic_inc_return(&req->ctx->cancel_seq),
	};
	int ret;

	if (cd.flags & IORING_ASYNC_CANCEL_FD) {
		if (req->flags & REQ_F_FIXED_FILE)
			req->file = io_file_get_fixed(req, req->cancel.fd,
							issue_flags);
		else
			req->file = io_file_get_normal(req, req->cancel.fd);
		if (!req->file) {
			ret = -EBADF;
			goto done;
		}
		cd.file = req->file;
	}

	ret = __io_async_cancel(&cd, req, issue_flags);
done:
	if (ret < 0)
		req_set_fail(req);
	io_req_complete_post(req, ret, 0);
	return 0;