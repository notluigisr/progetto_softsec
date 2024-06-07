	__acquires(&tasklist_lock)
{
	struct task_struct *p, *n;
	LIST_HEAD(ptrace_dead);

	if (likely(list_empty(&tracer->ptraced)))
		return;

	list_for_each_entry_safe(p, n, &tracer->ptraced, ptrace_entry) {
		if (unlikely(p->ptrace & PT_EXITKILL))
			send_sig_info(SIGKILL, SEND_SIG_FORCED, p);

		if (__ptrace_detach(tracer, p))
			list_add(&p->ptrace_entry, &ptrace_dead);
	}

	write_unlock_irq(&tasklist_lock);
	BUG_ON(!list_empty(&tracer->ptraced));

	list_for_each_entry_safe(p, n, &ptrace_dead, ptrace_entry) {
		list_del_init(&p->ptrace_entry);
		release_task(p);
	}

	write_lock_irq(&tasklist_lock);
}