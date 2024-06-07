static bool io_work_cancel(struct io_worker *worker, void *cancel_data)
{
	struct io_cb_cancel_data *data = cancel_data;
	unsigned long flags;
	bool ret = false;

	
	spin_lock_irqsave(&worker->lock, flags);
	if (worker->cur_work &&
	    data->cancel(worker->cur_work, data->caller_data)) {
		send_sig(SIGINT, worker->task, 1);
		ret = true;
	}
	spin_unlock_irqrestore(&worker->lock, flags);

	return ret;
}