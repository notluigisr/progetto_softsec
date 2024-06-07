static void __svm_vcpu_reset(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm_vcpu_init_msrpm(vcpu, svm->msrpm);

	svm_init_osvw(vcpu);
	vcpu->arch.microcode_version = 0x01000065;
	svm->tsc_ratio_msr = kvm_default_tsc_scaling_ratio;

	if (sev_es_guest(vcpu->kvm))
		sev_es_vcpu_reset(svm);
}