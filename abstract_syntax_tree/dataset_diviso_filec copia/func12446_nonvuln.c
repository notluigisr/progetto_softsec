static inline u64 kvm_guest_supported_xfd(struct kvm_vcpu *vcpu)
{
	return kvm_guest_supported_xcr0(vcpu) & XFEATURE_MASK_USER_DYNAMIC;
}