static inline void vmcs_init(struct vmcs *vmcs)
{
	u64 phys_addr = __pa(per_cpu(vmxarea, raw_smp_processor_id()));

	if (!vmm_exclusive)
		kvm_cpu_vmxon(phys_addr);

	vmcs_clear(vmcs);

	if (!vmm_exclusive)
		kvm_cpu_vmxoff();
}