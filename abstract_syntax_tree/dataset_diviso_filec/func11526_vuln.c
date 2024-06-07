static void nested_vmcb02_prepare_control(struct vcpu_svm *svm)
{
	const u32 mask = V_INTR_MASKING_MASK | V_GIF_ENABLE_MASK | V_GIF_MASK;
	struct kvm_vcpu *vcpu = &svm->vcpu;

	

	
	WARN_ON(kvm_apicv_activated(svm->vcpu.kvm));

	
	svm->vmcb->control.nested_ctl = svm->vmcb01.ptr->control.nested_ctl;
	svm->vmcb->control.iopm_base_pa = svm->vmcb01.ptr->control.iopm_base_pa;
	svm->vmcb->control.msrpm_base_pa = svm->vmcb01.ptr->control.msrpm_base_pa;

	

	
	svm->vmcb->control.tlb_ctl = TLB_CONTROL_DO_NOTHING;

	
	if (nested_npt_enabled(svm))
		nested_svm_init_mmu_context(vcpu);

	svm->vmcb->control.tsc_offset = vcpu->arch.tsc_offset =
		vcpu->arch.l1_tsc_offset + svm->nested.ctl.tsc_offset;

	svm->vmcb->control.int_ctl             =
		(svm->nested.ctl.int_ctl & ~mask) |
		(svm->vmcb01.ptr->control.int_ctl & mask);

	svm->vmcb->control.virt_ext            = svm->nested.ctl.virt_ext;
	svm->vmcb->control.int_vector          = svm->nested.ctl.int_vector;
	svm->vmcb->control.int_state           = svm->nested.ctl.int_state;
	svm->vmcb->control.event_inj           = svm->nested.ctl.event_inj;
	svm->vmcb->control.event_inj_err       = svm->nested.ctl.event_inj_err;

	svm->vmcb->control.pause_filter_count  = svm->nested.ctl.pause_filter_count;
	svm->vmcb->control.pause_filter_thresh = svm->nested.ctl.pause_filter_thresh;

	nested_svm_transition_tlb_flush(vcpu);

	
	enter_guest_mode(vcpu);

	
	recalc_intercepts(svm);
}