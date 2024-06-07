static int handle_bus_lock_vmexit(struct kvm_vcpu *vcpu)
{
	
	to_vmx(vcpu)->exit_reason.bus_lock_detected = true;
	return 1;
}