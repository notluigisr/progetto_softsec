static void init_bsp(struct bus *cpu_bus)
{
	struct device_path cpu_path;
	struct cpu_info *info;

	
	fill_processor_name(processor_name);
	printk(BIOS_INFO, "STR", processor_name);

	
	enable_lapic();

	
	cpu_path.type = DEVICE_PATH_APIC;
	cpu_path.apic.apic_id = lapicid();

	
	info = cpu_info();
	info->cpu = alloc_find_dev(cpu_bus, &cpu_path);
	info->cpu->name = processor_name;

	if (info->index != 0)
		printk(BIOS_CRIT, "STR", info->index);

	
	cpu_add_map_entry(info->index);
}