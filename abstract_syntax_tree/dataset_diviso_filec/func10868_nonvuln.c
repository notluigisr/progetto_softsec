static int wait_task_continued(struct wait_opts *wo, struct task_struct *p)
{
	int retval;
	pid_t pid;
	uid_t uid;

	if (!unlikely(wo->wo_flags & WCONTINUED))
		return 0;

	if (!(p->signal->flags & SIGNAL_STOP_CONTINUED))
		return 0;

	spin_lock_irq(&p->sighand->siglock);
	
	if (!(p->signal->flags & SIGNAL_STOP_CONTINUED)) {
		spin_unlock_irq(&p->sighand->siglock);
		return 0;
	}
	if (!unlikely(wo->wo_flags & WNOWAIT))
		p->signal->flags &= ~SIGNAL_STOP_CONTINUED;
	uid = __task_cred(p)->uid;
	spin_unlock_irq(&p->sighand->siglock);

	pid = task_pid_vnr(p);
	get_task_struct(p);
	read_unlock(&tasklist_lock);

	if (!wo->wo_info) {
		retval = wo->wo_rusage
			? getrusage(p, RUSAGE_BOTH, wo->wo_rusage) : 0;
		put_task_struct(p);
		if (!retval && wo->wo_stat)
			retval = put_user(0xffff, wo->wo_stat);
		if (!retval)
			retval = pid;
	} else {
		retval = wait_noreap_copyout(wo, p, pid, uid,
					     CLD_CONTINUED, SIGCONT);
		BUG_ON(retval == 0);
	}

	return retval;
}