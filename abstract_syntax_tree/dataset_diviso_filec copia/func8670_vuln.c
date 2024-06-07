asmlinkage void bad_mode(struct pt_regs *regs, int reason, unsigned int esr)
{
	console_verbose();

	pr_crit("STR",
		handler[reason], esr);

	die("STR", regs, 0);
	local_irq_disable();
	panic("STR");
}