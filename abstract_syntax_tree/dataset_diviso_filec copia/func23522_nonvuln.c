static int io_do_iopoll(struct io_ring_ctx *ctx, unsigned int *nr_events,
			long min)
{
	struct io_kiocb *req, *tmp;
	LIST_HEAD(done);
	bool spin;
	int ret;

	
	spin = !ctx->poll_multi_file && *nr_events < min;

	ret = 0;
	list_for_each_entry_safe(req, tmp, &ctx->poll_list, list) {
		struct kiocb *kiocb = &req->rw.kiocb;

		
		if (req->flags & REQ_F_IOPOLL_COMPLETED) {
			list_move_tail(&req->list, &done);
			continue;
		}
		if (!list_empty(&done))
			break;

		ret = kiocb->ki_filp->f_op->iopoll(kiocb, spin);
		if (ret < 0)
			break;

		if (ret && spin)
			spin = false;
		ret = 0;
	}

	if (!list_empty(&done))
		io_iopoll_complete(ctx, nr_events, &done);

	return ret;
}