void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
{
	int idx;

	if (vcpu->preempted) {
		if (!vcpu->arch.guest_state_protected)
			vcpu->arch.preempted_in_kernel = !static_call(kvm_x86_get_cpl)(vcpu);

		
		idx = srcu_read_lock(&vcpu->kvm->srcu);
		if (kvm_xen_msr_enabled(vcpu->kvm))
			kvm_xen_runstate_set_preempted(vcpu);
		else
			kvm_steal_time_set_preempted(vcpu);
		srcu_read_unlock(&vcpu->kvm->srcu, idx);
	}

	static_call(kvm_x86_vcpu_put)(vcpu);
	vcpu->arch.last_host_tsc = rdtsc();
}