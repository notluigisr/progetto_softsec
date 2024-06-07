static void selinux_bprm_committed_creds(struct linux_binprm *bprm)
{
	const struct task_security_struct *tsec = current_security();
	struct itimerval itimer;
	u32 osid, sid;
	int rc, i;

	osid = tsec->osid;
	sid = tsec->sid;

	if (sid == osid)
		return;

	
	rc = avc_has_perm(osid, sid, SECCLASS_PROCESS, PROCESS__SIGINH, NULL);
	if (rc) {
		memset(&itimer, 0, sizeof itimer);
		for (i = 0; i < 3; i++)
			do_setitimer(i, &itimer, NULL);
		spin_lock_irq(&current->sighand->siglock);
		if (!(current->signal->flags & SIGNAL_GROUP_EXIT)) {
			__flush_signals(current);
			flush_signal_handlers(current, 1);
			sigemptyset(&current->blocked);
		}
		spin_unlock_irq(&current->sighand->siglock);
	}

	
	read_lock(&tasklist_lock);
	wake_up_interruptible(&current->real_parent->signal->wait_chldexit);
	read_unlock(&tasklist_lock);
}