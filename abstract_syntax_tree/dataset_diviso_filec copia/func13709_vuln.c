static void tm_unavailable(struct pt_regs *regs)
{
	pr_emerg("STR"
			"STR", regs->trap, regs->nip);
	die("STR", regs, SIGABRT);
}