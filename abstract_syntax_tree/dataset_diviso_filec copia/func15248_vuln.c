static inline void native_set_ldt(const void *addr, unsigned int entries)
{
	if (likely(entries == 0))
		asm volatile("STR" (0));
	else {
		unsigned cpu = smp_processor_id();
		ldt_desc ldt;

		set_tssldt_descriptor(&ldt, (unsigned long)addr,
				      DESC_LDT, entries * sizeof(ldt) - 1);
		write_gdt_entry(get_cpu_gdt_table(cpu), GDT_ENTRY_LDT,
				&ldt, DESC_LDT);
		asm volatile("STR" (GDT_ENTRY_LDT*8));
	}
}