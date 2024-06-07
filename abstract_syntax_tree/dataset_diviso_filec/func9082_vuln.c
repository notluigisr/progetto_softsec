 */
static int io_poll_check_events(struct io_kiocb *req, bool *locked)
{
	struct io_ring_ctx *ctx = req->ctx;
	int v, ret;

	
	if (unlikely(req->task->flags & PF_EXITING))
		return -ECANCELED;

	do {
		v = atomic_read(&req->poll_refs);

		
		if (WARN_ON_ONCE(!(v & IO_POLL_REF_MASK)))
			return 0;
		if (v & IO_POLL_CANCEL_FLAG)
			return -ECANCELED;

		if (!req->cqe.res) {
			struct poll_table_struct pt = { ._key = req->apoll_events };
			unsigned flags = locked ? 0 : IO_URING_F_UNLOCKED;

			if (unlikely(!io_assign_file(req, flags)))
				return -EBADF;
			req->cqe.res = vfs_poll(req->file, &pt) & req->apoll_events;
		}

		if ((unlikely(!req->cqe.res)))
			continue;
		if (req->apoll_events & EPOLLONESHOT)
			return 0;

		
		if (!(req->flags & REQ_F_APOLL_MULTISHOT)) {
			__poll_t mask = mangle_poll(req->cqe.res &
						    req->apoll_events);
			bool filled;

			spin_lock(&ctx->completion_lock);
			filled = io_fill_cqe_aux(ctx, req->cqe.user_data,
						 mask, IORING_CQE_F_MORE);
			io_commit_cqring(ctx);
			spin_unlock(&ctx->completion_lock);
			if (filled) {
				io_cqring_ev_posted(ctx);
				continue;
			}
			return -ECANCELED;
		}

		io_tw_lock(req->ctx, locked);
		if (unlikely(req->task->flags & PF_EXITING))
			return -EFAULT;
		ret = io_issue_sqe(req,
				   IO_URING_F_NONBLOCK|IO_URING_F_COMPLETE_DEFER);
		if (ret)
			return ret;

		
	} while (atomic_sub_return(v & IO_POLL_REF_MASK, &req->poll_refs));

	return 1;