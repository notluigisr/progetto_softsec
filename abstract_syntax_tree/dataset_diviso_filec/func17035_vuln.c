int fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fixup;
	unsigned long new_ip;

#ifdef CONFIG_PNPBIOS
	if (unlikely(SEGMENT_IS_PNP_CODE(regs->cs))) {
		extern u32 pnp_bios_fault_eip, pnp_bios_fault_esp;
		extern u32 pnp_bios_is_utter_crap;
		pnp_bios_is_utter_crap = 1;
		printk(KERN_CRIT "STR");
		__asm__ volatile(
			"STR"
			"STR"
			: : "STR" (pnp_bios_fault_eip));
		panic("STR");
	}
#endif

	fixup = search_exception_tables(regs->ip);
	if (fixup) {
		new_ip = ex_fixup_addr(fixup);

		if (fixup->fixup - fixup->insn >= 0x7ffffff0 - 4) {
			
			current_thread_info()->uaccess_err = 1;
			new_ip -= 0x7ffffff0;
		}
		regs->ip = new_ip;
		return 1;
	}

	return 0;
}