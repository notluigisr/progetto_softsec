void kvm_post_set_cr4(struct kvm_vcpu *vcpu, unsigned long old_cr4, unsigned long cr4)
{
	if ((cr4 ^ old_cr4) & KVM_MMU_CR4_ROLE_BITS)
		kvm_mmu_reset_context(vcpu);

	
	if (!tdp_enabled &&
	    (cr4 & X86_CR4_PCIDE) && !(old_cr4 & X86_CR4_PCIDE))
		kvm_mmu_unload(vcpu);

	
	if (((cr4 ^ old_cr4) & X86_CR4_PGE) ||
	    (!(cr4 & X86_CR4_PCIDE) && (old_cr4 & X86_CR4_PCIDE)))
		kvm_make_request(KVM_REQ_TLB_FLUSH_GUEST, vcpu);

	
	else if (((cr4 ^ old_cr4) & X86_CR4_PAE) ||
		 ((cr4 & X86_CR4_SMEP) && !(old_cr4 & X86_CR4_SMEP)))
		kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);

}