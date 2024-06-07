
static void io_wq_submit_work(struct io_wq_work *work)
{
	struct io_kiocb *req = container_of(work, struct io_kiocb, work);
	struct io_kiocb *timeout;
	int ret = 0;

	timeout = io_prep_linked_timeout(req);
	if (timeout)
		io_queue_linked_timeout(timeout);

	if (work->flags & IO_WQ_WORK_CANCEL)
		ret = -ECANCELED;

	if (!ret) {
		do {
			ret = io_issue_sqe(req, 0);
			
			if (ret != -EAGAIN)
				break;
			cond_resched();
		} while (1);
	}

	
	if (ret) {
		
		refcount_inc(&req->refs);
		io_req_task_queue_fail(req, ret);
	}