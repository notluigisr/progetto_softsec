static void coredump_finish(struct mm_struct *mm)
{
	struct core_thread *curr, *next;
	struct task_struct *task;

	next = mm->core_state->dumper.next;
	while ((curr = next) != NULL) {
		next = curr->next;
		task = curr->task;
		
		smp_mb();
		curr->task = NULL;
		wake_up_process(task);
	}

	mm->core_state = NULL;
}