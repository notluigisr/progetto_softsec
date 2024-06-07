void altivec_assist_exception(struct pt_regs *regs)
{
	int err;

	if (!user_mode(regs)) {
		printk(KERN_EMERG "STR"
		       "STR", regs->nip);
		die("STR", regs, SIGILL);
	}

	flush_altivec_to_thread(current);

	PPC_WARN_EMULATED(altivec, regs);
	err = emulate_altivec(regs);
	if (err == 0) {
		regs->nip += 4;		
		emulate_single_step(regs);
		return;
	}

	if (err == -EFAULT) {
		
		_exception(SIGSEGV, regs, SEGV_ACCERR, regs->nip);
	} else {
		
		
		printk_ratelimited(KERN_ERR "STR"
				   "STR", current->comm, regs->nip);
		current->thread.vr_state.vscr.u[3] |= 0x10000;
	}
}