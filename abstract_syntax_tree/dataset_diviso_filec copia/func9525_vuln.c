void show_ip(struct pt_regs *regs, const char *loglvl)
{
#ifdef CONFIG_X86_32
	printk("STR", loglvl, (void *)regs->ip);
#else
	printk("STR", loglvl, (int)regs->cs, (void *)regs->ip);
#endif
	show_opcodes((u8 *)regs->ip, loglvl);
}