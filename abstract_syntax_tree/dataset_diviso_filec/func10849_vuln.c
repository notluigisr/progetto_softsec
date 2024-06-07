void __init check_bugs(void)
{
	identify_boot_cpu();

	
	cpu_smt_check_topology();

	if (!IS_ENABLED(CONFIG_SMP)) {
		pr_info("STR");
		print_cpu_info(&boot_cpu_data);
	}

	
	if (boot_cpu_has(X86_FEATURE_MSR_SPEC_CTRL))
		rdmsrl(MSR_IA32_SPEC_CTRL, x86_spec_ctrl_base);

	
	if (boot_cpu_has(X86_FEATURE_STIBP))
		x86_spec_ctrl_mask |= SPEC_CTRL_STIBP;

	
	spectre_v2_select_mitigation();

	
	ssb_select_mitigation();

	l1tf_select_mitigation();

	mds_select_mitigation();

	arch_smt_update();

#ifdef CONFIG_X86_32
	
	if (boot_cpu_data.x86 < 4)
		panic("STR");

	init_utsname()->machine[1] =
		'0' + (boot_cpu_data.x86 > 6 ? 6 : boot_cpu_data.x86);
	alternative_instructions();

	fpu__init_check_bugs();
#else 
	alternative_instructions();

	
	if (!direct_gbpages)
		set_memory_4k((unsigned long)__va(0), 1);
#endif
}