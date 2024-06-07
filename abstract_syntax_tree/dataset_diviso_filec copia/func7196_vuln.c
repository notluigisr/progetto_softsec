do_notify_resume_user(sigset_t *unused, struct sigscratch *scr, long in_syscall)
{
	if (fsys_mode(current, &scr->pt)) {
		
		if (!ia64_psr(&scr->pt)->lp)
			ia64_psr(&scr->pt)->lp = 1;
		return;
	}

#ifdef CONFIG_PERFMON
	if (current->thread.pfm_needs_checking)
		
		pfm_handle_work();
#endif

	
	if (test_thread_flag(TIF_SIGPENDING)) {
		local_irq_enable();	
		ia64_do_signal(scr, in_syscall);
	}

	if (test_thread_flag(TIF_NOTIFY_RESUME)) {
		clear_thread_flag(TIF_NOTIFY_RESUME);
		tracehook_notify_resume(&scr->pt);
	}

	
	if (unlikely(test_thread_flag(TIF_RESTORE_RSE))) {
		local_irq_enable();	
		ia64_sync_krbs();
	}

	local_irq_disable();	
}