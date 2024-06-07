static int FNAME(sync_page)(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
{
	int i, offset, nr_present;
	bool host_writable;
	gpa_t first_pte_gpa;

	offset = nr_present = 0;

	
	BUG_ON(sp->role.direct);

	if (PTTYPE == 32)
		offset = sp->role.quadrant << PT64_LEVEL_BITS;

	first_pte_gpa = gfn_to_gpa(sp->gfn) + offset * sizeof(pt_element_t);

	for (i = 0; i < PT64_ENT_PER_PAGE; i++) {
		unsigned pte_access;
		pt_element_t gpte;
		gpa_t pte_gpa;
		gfn_t gfn;

		if (!is_shadow_present_pte(sp->spt[i]))
			continue;

		pte_gpa = first_pte_gpa + i * sizeof(pt_element_t);

		if (kvm_read_guest_atomic(vcpu->kvm, pte_gpa, &gpte,
					  sizeof(pt_element_t)))
			return -EINVAL;

		gfn = gpte_to_gfn(gpte);

		if (FNAME(prefetch_invalid_gpte)(vcpu, sp, &sp->spt[i], gpte)) {
			vcpu->kvm->tlbs_dirty++;
			continue;
		}

		if (gfn != sp->gfns[i]) {
			drop_spte(vcpu->kvm, &sp->spt[i],
				      shadow_trap_nonpresent_pte);
			vcpu->kvm->tlbs_dirty++;
			continue;
		}

		nr_present++;
		pte_access = sp->role.access & FNAME(gpte_access)(vcpu, gpte);
		host_writable = sp->spt[i] & SPTE_HOST_WRITEABLE;

		set_spte(vcpu, &sp->spt[i], pte_access, 0, 0,
			 is_dirty_gpte(gpte), PT_PAGE_TABLE_LEVEL, gfn,
			 spte_to_pfn(sp->spt[i]), true, false,
			 host_writable);
	}

	return !nr_present;
}