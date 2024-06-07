static bool __cancel_work_timer(struct work_struct *work, bool is_dwork)
{
	static DECLARE_WAIT_QUEUE_HEAD(cancel_waitq);
	unsigned long flags;
	int ret;

	do {
		ret = try_to_grab_pending(work, is_dwork, &flags);
		
		if (unlikely(ret == -ENOENT)) {
			struct cwt_wait cwait;

			init_wait(&cwait.wait);
			cwait.wait.func = cwt_wakefn;
			cwait.work = work;

			prepare_to_wait_exclusive(&cancel_waitq, &cwait.wait,
						  TASK_UNINTERRUPTIBLE);
			if (work_is_canceling(work))
				schedule();
			finish_wait(&cancel_waitq, &cwait.wait);
		}
	} while (unlikely(ret < 0));

	
	mark_work_canceling(work);
	local_irq_restore(flags);

	
	if (wq_online)
		flush_work(work);

	clear_work_data(work);

	
	smp_mb();
	if (waitqueue_active(&cancel_waitq))
		__wake_up(&cancel_waitq, TASK_NORMAL, 1, work);

	return ret;
}