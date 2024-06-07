static bool ptrace_freeze_traced(struct task_struct *task)
{
	bool ret = false;

	
	if (task->jobctl & JOBCTL_LISTENING)
		return ret;

	spin_lock_irq(&task->sighand->siglock);
	if (task_is_traced(task) && !looks_like_a_spurious_pid(task) &&
	    !__fatal_signal_pending(task)) {
		WRITE_ONCE(task->__state, __TASK_TRACED);
		ret = true;
	}
	spin_unlock_irq(&task->sighand->siglock);

	return ret;
}