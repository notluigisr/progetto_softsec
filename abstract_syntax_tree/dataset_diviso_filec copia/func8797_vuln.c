static inline int restore_fpu_checking(struct task_struct *tsk)
{
	
	alternative_input(
		ASM_NOP8 ASM_NOP2,
		"STR"		
		"STR",	
		X86_FEATURE_FXSAVE_LEAK,
		[addr] "STR" (tsk->thread.fpu.has_fpu));

	return fpu_restore_checking(&tsk->thread.fpu);
}