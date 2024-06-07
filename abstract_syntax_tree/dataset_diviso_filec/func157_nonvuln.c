int kvm_emulate_xsetbv(struct kvm_vcpu *vcpu)
{
	if (static_call(kvm_x86_get_cpl)(vcpu) != 0 ||
	    __kvm_set_xcr(vcpu, kvm_rcx_read(vcpu), kvm_read_edx_eax(vcpu))) {
		kvm_inject_gp(vcpu, 0);
		return 1;
	}

	return kvm_skip_emulated_instruction(vcpu);
}