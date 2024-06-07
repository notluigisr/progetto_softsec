static int vmx_set_msr(struct kvm_vcpu *vcpu, u32 msr_index, u64 data)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct kvm_msr_entry *msr;
	u64 host_tsc;
	int ret = 0;

	switch (msr_index) {
#ifdef CONFIG_X86_64
	case MSR_EFER:
		vmx_load_host_state(vmx);
		ret = kvm_set_msr_common(vcpu, msr_index, data);
		break;
	case MSR_FS_BASE:
		vmcs_writel(GUEST_FS_BASE, data);
		break;
	case MSR_GS_BASE:
		vmcs_writel(GUEST_GS_BASE, data);
		break;
#endif
	case MSR_IA32_SYSENTER_CS:
		vmcs_write32(GUEST_SYSENTER_CS, data);
		break;
	case MSR_IA32_SYSENTER_EIP:
		vmcs_writel(GUEST_SYSENTER_EIP, data);
		break;
	case MSR_IA32_SYSENTER_ESP:
		vmcs_writel(GUEST_SYSENTER_ESP, data);
		break;
	case MSR_IA32_TIME_STAMP_COUNTER:
		rdtscll(host_tsc);
		guest_write_tsc(data, host_tsc);
		break;
	case MSR_P6_PERFCTR0:
	case MSR_P6_PERFCTR1:
	case MSR_P6_EVNTSEL0:
	case MSR_P6_EVNTSEL1:
		
		pr_unimpl(vcpu, "STR", msr_index, data);

		break;
	case MSR_IA32_CR_PAT:
		if (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) {
			vmcs_write64(GUEST_IA32_PAT, data);
			vcpu->arch.pat = data;
			break;
		}
		
	default:
		vmx_load_host_state(vmx);
		msr = find_msr_entry(vmx, msr_index);
		if (msr) {
			msr->data = data;
			break;
		}
		ret = kvm_set_msr_common(vcpu, msr_index, data);
	}

	return ret;
}