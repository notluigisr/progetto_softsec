static noinline uint32_t __kvm_cpuid_base(void)
{
	if (boot_cpu_data.cpuid_level < 0)
		return 0;	

	if (cpu_has_hypervisor)
		return hypervisor_cpuid_base("STR", 0);

	return 0;
}