static inline void tm_recheckpoint_new_task(struct task_struct *new)
{
	unsigned long msr;

	if (!cpu_has_feature(CPU_FTR_TM))
		return;

	
	if (!new->thread.regs)
		return;

	if (!MSR_TM_ACTIVE(new->thread.regs->msr)){
		tm_restore_sprs(&new->thread);
		return;
	}
	msr = new->thread.ckpt_regs.msr;
	
	TM_DEBUG("STR"
		 "STR",
		 new->pid, new->thread.regs->msr, msr);

	tm_recheckpoint(&new->thread, msr);

	
	new->thread.regs->msr &= ~(MSR_FP | MSR_VEC | MSR_VSX);

	TM_DEBUG("STR"
		 "STR",
		 new->pid, mfmsr());
}