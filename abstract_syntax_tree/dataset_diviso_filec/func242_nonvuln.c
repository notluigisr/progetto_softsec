static void vmx_load_mmu_pgd(struct kvm_vcpu *vcpu, hpa_t root_hpa,
			     int root_level)
{
	struct kvm *kvm = vcpu->kvm;
	bool update_guest_cr3 = true;
	unsigned long guest_cr3;
	u64 eptp;

	if (enable_ept) {
		eptp = construct_eptp(vcpu, root_hpa, root_level);
		vmcs_write64(EPT_POINTER, eptp);

		hv_track_root_tdp(vcpu, root_hpa);

		if (!enable_unrestricted_guest && !is_paging(vcpu))
			guest_cr3 = to_kvm_vmx(kvm)->ept_identity_map_addr;
		else if (kvm_register_is_dirty(vcpu, VCPU_EXREG_CR3))
			guest_cr3 = vcpu->arch.cr3;
		else 
			update_guest_cr3 = false;
		vmx_ept_load_pdptrs(vcpu);
	} else {
		guest_cr3 = root_hpa | kvm_get_active_pcid(vcpu);
	}

	if (update_guest_cr3)
		vmcs_writel(GUEST_CR3, guest_cr3);
}