static int svm_smi_allowed(struct kvm_vcpu *vcpu, bool for_injection)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	if (svm->nested.nested_run_pending)
		return -EBUSY;

	
	if (for_injection && is_guest_mode(vcpu) && nested_exit_on_smi(svm))
		return -EBUSY;

	return !svm_smi_blocked(vcpu);
}