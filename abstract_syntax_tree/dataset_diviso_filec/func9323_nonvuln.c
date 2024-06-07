save_fpu_state(struct pt_regs *regs, __siginfo_fpu_t __user *fpu)
{
	int err = 0;
#ifdef CONFIG_SMP
	if (test_tsk_thread_flag(current, TIF_USEDFPU)) {
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thread.float_regs[0], &current->thread.fsr,
		       &current->thread.fpqueue[0], &current->thread.fpqdepth);
		regs->psr &= ~(PSR_EF);
		clear_tsk_thread_flag(current, TIF_USEDFPU);
	}
#else
	if (current == last_task_used_math) {
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thread.float_regs[0], &current->thread.fsr,
		       &current->thread.fpqueue[0], &current->thread.fpqdepth);
		last_task_used_math = NULL;
		regs->psr &= ~(PSR_EF);
	}
#endif
	err |= __copy_to_user(&fpu->si_float_regs[0],
			      &current->thread.float_regs[0],
			      (sizeof(unsigned long) * 32));
	err |= __put_user(current->thread.fsr, &fpu->si_fsr);
	err |= __put_user(current->thread.fpqdepth, &fpu->si_fpqdepth);
	if (current->thread.fpqdepth != 0)
		err |= __copy_to_user(&fpu->si_fpqueue[0],
				      &current->thread.fpqueue[0],
				      ((sizeof(unsigned long) +
				      (sizeof(unsigned long *)))*16));
	clear_used_math();
	return err;
}