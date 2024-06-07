	__releases(&current->sighand->siglock)
{
	
	if ((current->jobctl & (JOBCTL_PENDING_MASK | JOBCTL_TRAP_FREEZE)) !=
	     JOBCTL_TRAP_FREEZE) {
		spin_unlock_irq(&current->sighand->siglock);
		return;
	}

	
	__set_current_state(TASK_INTERRUPTIBLE);
	clear_thread_flag(TIF_SIGPENDING);
	spin_unlock_irq(&current->sighand->siglock);
	cgroup_enter_frozen();
	freezable_schedule();
}