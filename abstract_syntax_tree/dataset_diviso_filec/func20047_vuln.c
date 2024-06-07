static unsigned long __peek_user(struct task_struct *child, addr_t addr)
{
	struct user *dummy = NULL;
	addr_t offset, tmp;

	if (addr < (addr_t) &dummy->regs.acrs) {
		
		tmp = *(addr_t *)((addr_t) &task_pt_regs(child)->psw + addr);
		if (addr == (addr_t) &dummy->regs.psw.mask)
			
			tmp &= ~PSW_MASK_PER;

	} else if (addr < (addr_t) &dummy->regs.orig_gpr2) {
		
		offset = addr - (addr_t) &dummy->regs.acrs;
#ifdef CONFIG_64BIT
		
		if (addr == (addr_t) &dummy->regs.acrs[15])
			tmp = ((unsigned long) child->thread.acrs[15]) << 32;
		else
#endif
		tmp = *(addr_t *)((addr_t) &child->thread.acrs + offset);

	} else if (addr == (addr_t) &dummy->regs.orig_gpr2) {
		
		tmp = (addr_t) task_pt_regs(child)->orig_gpr2;

	} else if (addr < (addr_t) (&dummy->regs.fp_regs + 1)) {
		
		offset = addr - (addr_t) &dummy->regs.fp_regs;
		tmp = *(addr_t *)((addr_t) &child->thread.fp_regs + offset);
		if (addr == (addr_t) &dummy->regs.fp_regs.fpc)
			tmp &= (unsigned long) FPC_VALID_MASK
				<< (BITS_PER_LONG - 32);

	} else if (addr < (addr_t) (&dummy->regs.per_info + 1)) {
		
		offset = addr - (addr_t) &dummy->regs.per_info;
		tmp = *(addr_t *)((addr_t) &child->thread.per_info + offset);

	} else
		tmp = 0;

	return tmp;
}