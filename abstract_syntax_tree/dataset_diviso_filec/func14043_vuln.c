static unsigned long convert_eip_to_linear(struct task_struct *child, struct pt_regs *regs)
{
	unsigned long addr, seg;

	addr = regs->eip;
	seg = regs->xcs & 0xffff;
	if (regs->eflags & VM_MASK) {
		addr = (addr & 0xffff) + (seg << 4);
		return addr;
	}

	
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