 */
static int io_uring_add_task_file(struct io_ring_ctx *ctx, struct file *file)
{
	struct io_uring_task *tctx = current->io_uring;
	int ret;

	if (unlikely(!tctx)) {
		ret = io_uring_alloc_task_context(current, ctx);
		if (unlikely(ret))
			return ret;
		tctx = current->io_uring;
	}
	if (tctx->last != file) {
		void *old = xa_load(&tctx->xa, (unsigned long)file);

		if (!old) {
			get_file(file);
			ret = xa_err(xa_store(&tctx->xa, (unsigned long)file,
						file, GFP_KERNEL));
			if (ret) {
				fput(file);
				return ret;
			}

			
			WARN_ON_ONCE((ctx->flags & IORING_SETUP_SQPOLL) &&
				     current != ctx->sqo_task);
		}
		tctx->last = file;
	}

	
	if (!tctx->sqpoll && (ctx->flags & IORING_SETUP_SQPOLL))
		tctx->sqpoll = true;

	return 0;