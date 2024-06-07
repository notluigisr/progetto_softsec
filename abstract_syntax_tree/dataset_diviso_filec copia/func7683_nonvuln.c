static int cr8_write_interception(struct kvm_vcpu *vcpu)
{
	int r;

	u8 cr8_prev = kvm_get_cr8(vcpu);
	
	r = cr_interception(vcpu);
	if (lapic_in_kernel(vcpu))
		return r;
	if (cr8_prev <= kvm_get_cr8(vcpu))
		return r;
	vcpu->run->exit_reason = KVM_EXIT_SET_TPR;
	return 0;
}