int kvm_emulate_wrmsr(struct kvm_vcpu *vcpu)
{
	u32 ecx = kvm_rcx_read(vcpu);
	u64 data = kvm_read_edx_eax(vcpu);
	int r;

	r = kvm_set_msr(vcpu, ecx, data);

	if (!r) {
		trace_kvm_msr_write(ecx, data);
	} else {
		
		if (kvm_msr_user_space(vcpu, ecx, KVM_EXIT_X86_WRMSR, data,
				       complete_fast_msr_access, r))
			return 0;
		
		if (r < 0)
			return r;
		trace_kvm_msr_write_ex(ecx, data);
	}

	return static_call(kvm_x86_complete_emulated_msr)(vcpu, r);
}