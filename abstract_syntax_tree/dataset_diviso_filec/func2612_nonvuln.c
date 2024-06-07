static int emulate_math(struct pt_regs *regs)
{
	int ret;
	extern int do_mathemu(struct pt_regs *regs);

	ret = do_mathemu(regs);
	if (ret >= 0)
		PPC_WARN_EMULATED(math, regs);

	switch (ret) {
	case 0:
		emulate_single_step(regs);
		return 0;
	case 1: {
			int code = 0;
			code = __parse_fpscr(current->thread.fp_state.fpscr);
			_exception(SIGFPE, regs, code, regs->nip);
			return 0;
		}
	case -EFAULT:
		_exception(SIGSEGV, regs, SEGV_MAPERR, regs->nip);
		return 0;
	}

	return -1;
}