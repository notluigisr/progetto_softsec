int kvm_skip_emulated_instruction(struct kvm_vcpu *vcpu)
{
	unsigned long rflags = static_call(kvm_x86_get_rflags)(vcpu);
	int r;

	r = static_call(kvm_x86_skip_emulated_instruction)(vcpu);
	if (unlikely(!r))
		return 0;

	kvm_pmu_trigger_event(vcpu, PERF_COUNT_HW_INSTRUCTIONS);

	
	if (unlikely(rflags & X86_EFLAGS_TF))
		r = kvm_vcpu_do_singlestep(vcpu);
	return r;
}