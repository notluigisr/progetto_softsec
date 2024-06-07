int kvm_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
{
	bool skip_tlb_flush = false;
	unsigned long pcid = 0;
#ifdef CONFIG_X86_64
	bool pcid_enabled = kvm_read_cr4_bits(vcpu, X86_CR4_PCIDE);

	if (pcid_enabled) {
		skip_tlb_flush = cr3 & X86_CR3_PCID_NOFLUSH;
		cr3 &= ~X86_CR3_PCID_NOFLUSH;
		pcid = cr3 & X86_CR3_PCID_MASK;
	}
#endif

	
	if (cr3 == kvm_read_cr3(vcpu) && !is_pae_paging(vcpu))
		goto handle_tlb_flush;

	
	if (kvm_vcpu_is_illegal_gpa(vcpu, cr3))
		return 1;

	if (is_pae_paging(vcpu) && !load_pdptrs(vcpu, cr3))
		return 1;

	if (cr3 != kvm_read_cr3(vcpu))
		kvm_mmu_new_pgd(vcpu, cr3);

	vcpu->arch.cr3 = cr3;
	kvm_register_mark_dirty(vcpu, VCPU_EXREG_CR3);

handle_tlb_flush:
	
	if (!skip_tlb_flush)
		kvm_invalidate_pcid(vcpu, pcid);

	return 0;
}