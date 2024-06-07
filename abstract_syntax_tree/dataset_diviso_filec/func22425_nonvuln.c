static void update_intel_pt_cfg(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct kvm_cpuid_entry2 *best = NULL;
	int i;

	for (i = 0; i < PT_CPUID_LEAVES; i++) {
		best = kvm_find_cpuid_entry(vcpu, 0x14, i);
		if (!best)
			return;
		vmx->pt_desc.caps[CPUID_EAX + i*PT_CPUID_REGS_NUM] = best->eax;
		vmx->pt_desc.caps[CPUID_EBX + i*PT_CPUID_REGS_NUM] = best->ebx;
		vmx->pt_desc.caps[CPUID_ECX + i*PT_CPUID_REGS_NUM] = best->ecx;
		vmx->pt_desc.caps[CPUID_EDX + i*PT_CPUID_REGS_NUM] = best->edx;
	}

	
	vmx->pt_desc.num_address_ranges = intel_pt_validate_cap(vmx->pt_desc.caps,
						PT_CAP_num_address_ranges);

	
	vmx->pt_desc.ctl_bitmask = ~(RTIT_CTL_TRACEEN | RTIT_CTL_OS |
			RTIT_CTL_USR | RTIT_CTL_TSC_EN | RTIT_CTL_DISRETC |
			RTIT_CTL_BRANCH_EN);

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_cr3_filtering))
		vmx->pt_desc.ctl_bitmask &= ~RTIT_CTL_CR3EN;

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_psb_cyc))
		vmx->pt_desc.ctl_bitmask &= ~(RTIT_CTL_CYCLEACC |
				RTIT_CTL_CYC_THRESH | RTIT_CTL_PSB_FREQ);

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_mtc))
		vmx->pt_desc.ctl_bitmask &= ~(RTIT_CTL_MTC_EN |
					      RTIT_CTL_MTC_RANGE);

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_ptwrite))
		vmx->pt_desc.ctl_bitmask &= ~(RTIT_CTL_FUP_ON_PTW |
							RTIT_CTL_PTW_EN);

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_power_event_trace))
		vmx->pt_desc.ctl_bitmask &= ~RTIT_CTL_PWR_EVT_EN;

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_topa_output))
		vmx->pt_desc.ctl_bitmask &= ~RTIT_CTL_TOPA;

	
	if (intel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_output_subsys))
		vmx->pt_desc.ctl_bitmask &= ~RTIT_CTL_FABRIC_EN;

	
	for (i = 0; i < vmx->pt_desc.num_address_ranges; i++)
		vmx->pt_desc.ctl_bitmask &= ~(0xfULL << (32 + i * 4));
}