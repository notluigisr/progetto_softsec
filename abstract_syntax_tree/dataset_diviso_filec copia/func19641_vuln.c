show_signal_msg(struct pt_regs *regs, unsigned long error_code,
		unsigned long address, struct task_struct *tsk)
{
	const char *loglvl = task_pid_nr(tsk) > 1 ? KERN_INFO : KERN_EMERG;

	if (!unhandled_signal(tsk, SIGSEGV))
		return;

	if (!printk_ratelimit())
		return;

	printk("STR",
		loglvl, tsk->comm, task_pid_nr(tsk), address,
		(void *)regs->ip, (void *)regs->sp, error_code);

	print_vma_addr(KERN_CONT "STR", regs->ip);

	printk(KERN_CONT "STR");

	show_opcodes((u8 *)regs->ip, loglvl);
}