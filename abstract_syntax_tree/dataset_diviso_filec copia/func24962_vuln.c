int xstateregs_set(struct task_struct *target, const struct user_regset *regset,
		  unsigned int pos, unsigned int count,
		  const void *kbuf, const void __user *ubuf)
{
	struct fpu *fpu = &target->thread.fpu;
	struct xregs_state *xsave;
	int ret;

	if (!boot_cpu_has(X86_FEATURE_XSAVE))
		return -ENODEV;

	
	if ((pos != 0) || (count < fpu_user_xstate_size))
		return -EFAULT;

	xsave = &fpu->state.xsave;

	fpu__activate_fpstate_write(fpu);

	if (boot_cpu_has(X86_FEATURE_XSAVES)) {
		if (kbuf)
			ret = copy_kernel_to_xstate(xsave, kbuf);
		else
			ret = copy_user_to_xstate(xsave, ubuf);
	} else {
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, xsave, 0, -1);
	}

	
	if (ret)
		fpstate_init(&fpu->state);

	
	xsave->i387.mxcsr &= mxcsr_feature_mask;
	xsave->header.xfeatures &= xfeatures_mask;
	
	memset(&xsave->header.reserved, 0, 48);

	return ret;
}