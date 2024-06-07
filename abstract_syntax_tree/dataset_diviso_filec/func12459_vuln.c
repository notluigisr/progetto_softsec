void __kthread_queue_delayed_work(struct kthread_worker *worker,
				  struct kthread_delayed_work *dwork,
				  unsigned long delay)
{
	struct timer_list *timer = &dwork->timer;
	struct kthread_work *work = &dwork->work;

	WARN_ON_ONCE(timer->function != kthread_delayed_work_timer_fn ||
		     timer->data != (unsigned long)dwork);

	
	if (!delay) {
		kthread_insert_work(worker, work, &worker->work_list);
		return;
	}

	
	kthread_insert_work_sanity_check(worker, work);

	list_add(&work->node, &worker->delayed_work_list);
	work->worker = worker;
	timer_stats_timer_set_start_info(&dwork->timer);
	timer->expires = jiffies + delay;
	add_timer(timer);
}