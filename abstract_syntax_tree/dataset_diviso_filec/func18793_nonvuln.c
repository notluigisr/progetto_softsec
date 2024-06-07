static void svm_prepare_switch_to_guest(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct svm_cpu_data *sd = per_cpu(svm_data, vcpu->cpu);

	if (sev_es_guest(vcpu->kvm))
		sev_es_unmap_ghcb(svm);

	if (svm->guest_state_loaded)
		return;

	
	vmsave(__sme_page_pa(sd->save_area));
	if (sev_es_guest(vcpu->kvm)) {
		struct vmcb_save_area *hostsa;
		hostsa = (struct vmcb_save_area *)(page_address(sd->save_area) + 0x400);

		sev_es_prepare_switch_to_guest(hostsa);
	}

	if (tsc_scaling)
		__svm_write_tsc_multiplier(vcpu->arch.tsc_scaling_ratio);

	if (likely(tsc_aux_uret_slot >= 0))
		kvm_set_user_return_msr(tsc_aux_uret_slot, svm->tsc_aux, -1ull);

	svm->guest_state_loaded = true;
}