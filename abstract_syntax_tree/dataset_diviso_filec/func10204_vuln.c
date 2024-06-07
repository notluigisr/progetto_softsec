					   struct io_cancel_data *cd)
	__must_hold(&ctx->timeout_lock)
{
	struct io_timeout_data *io;
	struct io_kiocb *req;
	bool found = false;

	list_for_each_entry(req, &ctx->timeout_list, timeout.list) {
		if (!(cd->flags & IORING_ASYNC_CANCEL_ANY) &&
		    cd->data != req->cqe.user_data)
			continue;
		if (cd->flags & (IORING_ASYNC_CANCEL_ALL|IORING_ASYNC_CANCEL_ANY)) {
			if (cd->seq == req->work.cancel_seq)
				continue;
			req->work.cancel_seq = cd->seq;
		}
		found = true;
		break;
	}
	if (!found)
		return ERR_PTR(-ENOENT);

	io = req->async_data;
	if (hrtimer_try_to_cancel(&io->timer) == -1)
		return ERR_PTR(-EALREADY);
	list_del_init(&req->timeout.list);
	return req;