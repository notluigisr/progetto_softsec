static void kvm_arch_vcpu_guestdbg_update_apicv_inhibit(struct kvm *kvm)
{
	bool inhibit = false;
	struct kvm_vcpu *vcpu;
	unsigned long i;

	down_write(&kvm->arch.apicv_update_lock);

	kvm_for_each_vcpu(i, vcpu, kvm) {
		if (vcpu->guest_debug & KVM_GUESTDBG_BLOCKIRQ) {
			inhibit = true;
			break;
		}
	}
	__kvm_request_apicv_update(kvm, !inhibit, APICV_INHIBIT_REASON_BLOCKIRQ);
	up_write(&kvm->arch.apicv_update_lock);
}