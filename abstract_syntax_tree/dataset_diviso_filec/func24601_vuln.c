unsigned long convert_rip_to_linear(struct task_struct *child, struct pt_regs *regs)
{
	unsigned long addr, seg;

	addr = regs->rip;
	seg = regs->cs & 0xffff;

	
	if (seg & LDT_SEGMENT) {
		u32 *desc;
		unsigned long base;

		down(&child->mm->context.sem);
		desc = child->mm->context.ldt + (seg & ~7);
		base = (desc[0] >> 16) | ((desc[1] & 0xff) << 16) | (desc[1] & 0xff000000);

		
		if (!((desc[1] >> 22) & 1))
			addr &= 0xffff;
		addr += base;
		up(&child->mm->context.sem);
	}
	return addr;
}