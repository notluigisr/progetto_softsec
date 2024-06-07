asmlinkage void do_notify_resume(struct pt_regs *regs, u32 thread_info_flags)
{
	
	if (thread_info_flags & _TIF_SINGLESTEP) {
#ifndef CONFIG_MN10300_USING_JTAG
		regs->epsw |= EPSW_T;
		clear_thread_flag(TIF_SINGLESTEP);
#else
		BUG(); 
#endif
	}

	
	if (thread_info_flags & (_TIF_SIGPENDING | _TIF_RESTORE_SIGMASK))
		do_signal(regs);

	if (thread_info_flags & _TIF_NOTIFY_RESUME) {
		clear_thread_flag(TIF_NOTIFY_RESUME);
		tracehook_notify_resume(__frame);
	}
}