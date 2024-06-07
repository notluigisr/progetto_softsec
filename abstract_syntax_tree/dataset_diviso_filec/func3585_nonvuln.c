
static int io_uring_count_inflight(struct io_ring_ctx *ctx,
				   struct task_struct *task,
				   struct files_struct *files)
{
	struct io_kiocb *req;
	int cnt = 0;

	spin_lock_irq(&ctx->inflight_lock);
	list_for_each_entry(req, &ctx->inflight_list, inflight_entry)
		cnt += io_match_task(req, task, files);
	spin_unlock_irq(&ctx->inflight_lock);
	return cnt;