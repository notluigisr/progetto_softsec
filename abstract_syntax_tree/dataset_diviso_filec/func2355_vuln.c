static void __init xen_pv_init_platform(void)
{
	populate_extra_pte(fix_to_virt(FIX_PARAVIRT_BOOTMAP));

	set_fixmap(FIX_PARAVIRT_BOOTMAP, xen_start_info->shared_info);
	HYPERVISOR_shared_info = (void *)fix_to_virt(FIX_PARAVIRT_BOOTMAP);

	
	xen_vcpu_info_reset(0);

	
	xen_init_time_ops();
}