do_general_protection(struct pt_regs *regs, long error_code)
{
	struct task_struct *tsk;

	RCU_LOCKDEP_WARN(!rcu_is_watching(), "STR");
	conditional_sti(regs);

	if (v8086_mode(regs)) {
		local_irq_enable();
		handle_vm86_fault((struct kernel_vm86_regs *) regs, error_code);
		return;
	}

	tsk = current;
	if (!user_mode(regs)) {
		if (fixup_exception(regs))
			return;

		tsk->thread.error_code = error_code;
		tsk->thread.trap_nr = X86_TRAP_GP;
		if (notify_die(DIE_GPF, "STR", regs, error_code,
			       X86_TRAP_GP, SIGSEGV) != NOTIFY_STOP)
			die("STR", regs, error_code);
		return;
	}

	tsk->thread.error_code = error_code;
	tsk->thread.trap_nr = X86_TRAP_GP;

	if (show_unhandled_signals && unhandled_signal(tsk, SIGSEGV) &&
			printk_ratelimit()) {
		pr_info("STR",
			tsk->comm, task_pid_nr(tsk),
			regs->ip, regs->sp, error_code);
		print_vma_addr("STR", regs->ip);
		pr_cont("STR");
	}

	force_sig_info(SIGSEGV, SEND_SIG_PRIV, tsk);
}