handle_signal(unsigned long sig, siginfo_t *info, struct k_sigaction *ka,
	      sigset_t *oldset, struct pt_regs *regs)
{
	int ret;

	
	if (syscall_get_nr(current, regs) >= 0) {
		
		switch (syscall_get_error(current, regs)) {
		case -ERESTART_RESTARTBLOCK:
		case -ERESTARTNOHAND:
			regs->ax = -EINTR;
			break;

		case -ERESTARTSYS:
			if (!(ka->sa.sa_flags & SA_RESTART)) {
				regs->ax = -EINTR;
				break;
			}
		
		case -ERESTARTNOINTR:
			regs->ax = regs->orig_ax;
			regs->ip -= 2;
			break;
		}
	}

	
	if (unlikely(regs->flags & X86_EFLAGS_TF) &&
	    likely(test_and_clear_thread_flag(TIF_FORCED_TF)))
		regs->flags &= ~X86_EFLAGS_TF;

	ret = setup_rt_frame(sig, ka, info, oldset, regs);

	if (ret)
		return ret;

#ifdef CONFIG_X86_64
	
	set_fs(USER_DS);
#endif

	
	regs->flags &= ~X86_EFLAGS_DF;

	
	regs->flags &= ~X86_EFLAGS_TF;

	spin_lock_irq(&current->sighand->siglock);
	sigorsets(&current->blocked, &current->blocked, &ka->sa.sa_mask);
	if (!(ka->sa.sa_flags & SA_NODEFER))
		sigaddset(&current->blocked, sig);
	recalc_sigpending();
	spin_unlock_irq(&current->sighand->siglock);

	tracehook_signal_handler(sig, info, ka, regs,
				 test_thread_flag(TIF_SINGLESTEP));

	return 0;
}