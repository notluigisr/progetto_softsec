static void kvm_vcpu_init(struct kvm_vcpu *vcpu, struct kvm *kvm, unsigned id)
{
	mutex_init(&vcpu->mutex);
	vcpu->cpu = -1;
	vcpu->kvm = kvm;
	vcpu->vcpu_id = id;
	vcpu->pid = NULL;
#ifndef __KVM_HAVE_ARCH_WQP
	rcuwait_init(&vcpu->wait);
#endif
	kvm_async_pf_vcpu_init(vcpu);

	kvm_vcpu_set_in_spin_loop(vcpu, false);
	kvm_vcpu_set_dy_eligible(vcpu, false);
	vcpu->preempted = false;
	vcpu->ready = false;
	preempt_notifier_init(&vcpu->preempt_notifier, &kvm_preempt_ops);
	vcpu->last_used_slot = NULL;
}