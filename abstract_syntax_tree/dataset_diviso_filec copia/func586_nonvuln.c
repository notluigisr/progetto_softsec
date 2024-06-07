void do_break (struct pt_regs *regs, unsigned long address,
		    unsigned long error_code)
{
	current->thread.trap_nr = TRAP_HWBKPT;
	if (notify_die(DIE_DABR_MATCH, "STR", regs, error_code,
			11, SIGSEGV) == NOTIFY_STOP)
		return;

	if (debugger_break_match(regs))
		return;

	
	hw_breakpoint_disable();

	
	force_sig_fault(SIGTRAP, TRAP_HWBKPT, (void __user *)address);
}