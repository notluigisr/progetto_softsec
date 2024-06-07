static int install_permanent_handler(int num_cpus, uintptr_t smbase,
					size_t smsize, size_t save_state_size)
{
	
	struct smm_loader_params smm_params = {
		.per_cpu_stack_size = CONFIG_SMM_MODULE_STACK_SIZE,
		.num_concurrent_stacks = num_cpus,
		.per_cpu_save_state_size = save_state_size,
		.num_concurrent_save_states = num_cpus,
	};

	
	if (mp_state.ops.adjust_smm_params != NULL)
		mp_state.ops.adjust_smm_params(&smm_params, 1);

	printk(BIOS_DEBUG, "STR", smbase);

	if (smm_load_module((void *)smbase, smsize, &smm_params))
		return -1;

	adjust_smm_apic_id_map(&smm_params);

	return 0;
}