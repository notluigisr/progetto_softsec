bool __is_module_percpu_address(unsigned long addr, unsigned long *can_addr)
{
	struct module *mod;
	unsigned int cpu;

	preempt_disable();

	list_for_each_entry_rcu(mod, &modules, list) {
		if (mod->state == MODULE_STATE_UNFORMED)
			continue;
		if (!mod->percpu_size)
			continue;
		for_each_possible_cpu(cpu) {
			void *start = per_cpu_ptr(mod->percpu, cpu);
			void *va = (void *)addr;

			if (va >= start && va < start + mod->percpu_size) {
				if (can_addr) {
					*can_addr = (unsigned long) (va - start);
					*can_addr += (unsigned long)
						per_cpu_ptr(mod->percpu,
							    get_boot_cpu_id());
				}
				preempt_enable();
				return true;
			}
		}
	}

	preempt_enable();
	return false;
}