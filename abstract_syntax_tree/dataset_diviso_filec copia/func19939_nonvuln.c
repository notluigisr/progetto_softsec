static void emulate_single_step(struct pt_regs *regs)
{
	if (single_stepping(regs))
		single_step_exception(regs);
}