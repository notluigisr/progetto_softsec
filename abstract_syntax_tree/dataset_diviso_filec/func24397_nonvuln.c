static inline void kvm_make_request(int req, struct kvm_vcpu *vcpu)
{
	
	smp_wmb();
	set_bit(req & KVM_REQUEST_MASK, (void *)&vcpu->requests);
}