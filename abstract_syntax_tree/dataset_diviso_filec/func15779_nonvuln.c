asmlinkage void __sched preempt_schedule(void)
{
	struct thread_info *ti = current_thread_info();
	struct task_struct *task = current;
	int saved_lock_depth;

	
	if (likely(ti->preempt_count || irqs_disabled()))
		return;

	do {
		add_preempt_count(PREEMPT_ACTIVE);

		
		saved_lock_depth = task->lock_depth;
		task->lock_depth = -1;
		schedule();
		task->lock_depth = saved_lock_depth;
		sub_preempt_count(PREEMPT_ACTIVE);

		
		barrier();
	} while (unlikely(test_thread_flag(TIF_NEED_RESCHED)));
}