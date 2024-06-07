dotraplinkage void __kprobes do_debug(struct pt_regs *regs, long error_code)
{
	struct task_struct *tsk = current;
	int user_icebp = 0;
	unsigned long dr6;
	int si_code;

	get_debugreg(dr6, 6);

	
	dr6 &= ~DR6_RESERVED;

	
	if (!dr6 && user_mode(regs))
		user_icebp = 1;

	
	if ((dr6 & DR_STEP) && kmemcheck_trap(regs))
		return;

	
	set_debugreg(0, 6);

	
	clear_tsk_thread_flag(tsk, TIF_BLOCKSTEP);

	
	tsk->thread.debugreg6 = dr6;

	if (notify_die(DIE_DEBUG, "STR", regs, PTR_ERR(&dr6), error_code,
							SIGTRAP) == NOTIFY_STOP)
		return;

	
	preempt_conditional_sti(regs);

	if (regs->flags & X86_VM_MASK) {
		handle_vm86_trap((struct kernel_vm86_regs *) regs,
				error_code, 1);
		preempt_conditional_cli(regs);
		return;
	}

	
	if ((dr6 & DR_STEP) && !user_mode(regs)) {
		tsk->thread.debugreg6 &= ~DR_STEP;
		set_tsk_thread_flag(tsk, TIF_SINGLESTEP);
		regs->flags &= ~X86_EFLAGS_TF;
	}
	si_code = get_si_code(tsk->thread.debugreg6);
	if (tsk->thread.debugreg6 & (DR_STEP | DR_TRAP_BITS) || user_icebp)
		send_sigtrap(tsk, regs, error_code, si_code);
	preempt_conditional_cli(regs);

	return;
}