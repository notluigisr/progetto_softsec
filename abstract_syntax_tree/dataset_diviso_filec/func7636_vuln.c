static void __init xen_hvm_guest_init(void)
{
	if (xen_pv_domain())
		return;

	init_hvm_pv_info();

	reserve_shared_info();
	xen_hvm_init_shared_info();

	
	xen_vcpu_info_reset(0);

	xen_panic_handler_init();

	if (!no_vector_callback && xen_feature(XENFEAT_hvm_callback_vector))
		xen_have_vector_callback = 1;

	xen_hvm_smp_init();
	WARN_ON(xen_cpuhp_setup(xen_cpu_up_prepare_hvm, xen_cpu_dead_hvm));
	xen_unplug_emulated_devices();
	x86_init.irqs.intr_init = xen_init_IRQ;
	xen_hvm_init_time_ops();
	xen_hvm_init_mmu_ops();

#ifdef CONFIG_KEXEC_CORE
	machine_ops.shutdown = xen_hvm_shutdown;
	machine_ops.crash_shutdown = xen_hvm_crash_shutdown;
#endif
}