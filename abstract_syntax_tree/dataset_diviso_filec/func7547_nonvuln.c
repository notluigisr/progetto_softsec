bool kvm_arch_dy_has_pending_interrupt(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.apicv_active && static_call(kvm_x86_dy_apicv_has_pending_interrupt)(vcpu))
		return true;

	return false;
}