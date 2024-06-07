
static inline int io_cqring_wait_schedule(struct io_ring_ctx *ctx,
					  struct io_wait_queue *iowq,
					  signed long *timeout)
{
	int ret;

	
	ret = io_run_task_work_sig();
	if (ret || io_should_wake(iowq))
		return ret;
	
	if (test_bit(0, &ctx->check_cq_overflow))
		return 1;

	*timeout = schedule_timeout(*timeout);
	return !*timeout ? -ETIME : 1;