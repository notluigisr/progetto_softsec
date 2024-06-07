do_sigbus(struct pt_regs *regs, unsigned long error_code, unsigned long address,
	  unsigned int fault)
{
	struct task_struct *tsk = current;
	int code = BUS_ADRERR;

	
	if (!(error_code & PF_USER)) {
		no_context(regs, error_code, address, SIGBUS, BUS_ADRERR);
		return;
	}

	
	if (is_prefetch(regs, error_code, address))
		return;

	tsk->thread.cr2		= address;
	tsk->thread.error_code	= error_code;
	tsk->thread.trap_nr	= X86_TRAP_PF;

#ifdef CONFIG_MEMORY_FAILURE
	if (fault & (VM_FAULT_HWPOISON|VM_FAULT_HWPOISON_LARGE)) {
		printk(KERN_ERR
	"STR",
			tsk->comm, tsk->pid, address);
		code = BUS_MCEERR_AR;
	}
#endif
	force_sig_info_fault(SIGBUS, code, address, tsk, fault);
}