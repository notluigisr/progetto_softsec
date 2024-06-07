dotraplinkage void __kprobes do_int3(struct pt_regs *regs, long error_code)
{
#ifdef CONFIG_KGDB_LOW_LEVEL_TRAP
	if (kgdb_ll_trap(DIE_INT3, "STR", regs, error_code, 3, SIGTRAP)
			== NOTIFY_STOP)
		return;
#endif 
#ifdef CONFIG_KPROBES
	if (notify_die(DIE_INT3, "STR", regs, error_code, 3, SIGTRAP)
			== NOTIFY_STOP)
		return;
#else
	if (notify_die(DIE_TRAP, "STR", regs, error_code, 3, SIGTRAP)
			== NOTIFY_STOP)
		return;
#endif

	preempt_conditional_sti(regs);
	do_trap(3, SIGTRAP, "STR", regs, error_code, NULL);
	preempt_conditional_cli(regs);
}