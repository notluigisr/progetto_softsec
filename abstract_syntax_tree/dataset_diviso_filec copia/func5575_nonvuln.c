static int vmx_deliver_posted_interrupt(struct kvm_vcpu *vcpu, int vector)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int r;

	r = vmx_deliver_nested_posted_interrupt(vcpu, vector);
	if (!r)
		return 0;

	if (!vcpu->arch.apicv_active)
		return -1;

	if (pi_test_and_set_pir(vector, &vmx->pi_desc))
		return 0;

	
	if (pi_test_and_set_on(&vmx->pi_desc))
		return 0;

	
	kvm_vcpu_trigger_posted_interrupt(vcpu, POSTED_INTR_VECTOR);
	return 0;
}