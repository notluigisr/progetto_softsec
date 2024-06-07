default_idle (void)
{
	local_irq_enable();
	while (!need_resched()) {
		if (can_do_pal_halt) {
			local_irq_disable();
			if (!need_resched()) {
				safe_halt();
			}
			local_irq_enable();
		} else
			cpu_relax();
	}
}