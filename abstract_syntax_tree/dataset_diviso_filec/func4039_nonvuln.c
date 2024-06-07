sys_sigaltstack(const stack_t __user *uss, stack_t __user *uoss,
	        unsigned long r4, unsigned long r5, unsigned long r6,
	        unsigned long r7,
	        struct pt_regs * regs)
{
	return do_sigaltstack(uss, uoss, REF_REG_SP);
}