static void init_ppgtt_reg_state(u32 *regs, const struct i915_ppgtt *ppgtt)
{
	if (i915_vm_is_4lvl(&ppgtt->vm)) {
		
		ASSIGN_CTX_PML4(ppgtt, regs);
	} else {
		ASSIGN_CTX_PDP(ppgtt, regs, 3);
		ASSIGN_CTX_PDP(ppgtt, regs, 2);
		ASSIGN_CTX_PDP(ppgtt, regs, 1);
		ASSIGN_CTX_PDP(ppgtt, regs, 0);
	}
}