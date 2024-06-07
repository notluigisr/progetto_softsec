static int __kvm_emulate_halt(struct kvm_vcpu *vcpu, int state, int reason)
{
	
	++vcpu->stat.halt_exits;
	if (lapic_in_kernel(vcpu)) {
		vcpu->arch.mp_state = state;
		return 1;
	} else {
		vcpu->run->exit_reason = reason;
		return 0;
	}
}