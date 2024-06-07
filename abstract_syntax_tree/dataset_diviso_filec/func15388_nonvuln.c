				     struct io_cancel_data *cd)
	__must_hold(&ctx->completion_lock)
{
	struct hlist_head *list;
	struct io_kiocb *req;

	list = &ctx->cancel_hash[hash_long(cd->data, ctx->cancel_hash_bits)];
	hlist_for_each_entry(req, list, hash_node) {
		if (cd->data != req->cqe.user_data)
			continue;
		if (poll_only && req->opcode != IORING_OP_POLL_ADD)
			continue;
		if (cd->flags & IORING_ASYNC_CANCEL_ALL) {
			if (cd->seq == req->work.cancel_seq)
				continue;
			req->work.cancel_seq = cd->seq;
		}
		return req;
	}
	return NULL;