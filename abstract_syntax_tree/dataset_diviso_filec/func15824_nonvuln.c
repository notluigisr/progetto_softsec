int kvm_get_apic_interrupt(struct kvm_vcpu *vcpu)
{
	int vector = kvm_apic_has_interrupt(vcpu);
	struct kvm_lapic *apic = vcpu->arch.apic;
	u32 ppr;

	if (vector == -1)
		return -1;

	

	apic_clear_irr(vector, apic);
	if (to_hv_vcpu(vcpu) && test_bit(vector, to_hv_synic(vcpu)->auto_eoi_bitmap)) {
		
		apic_update_ppr(apic);
	} else {
		
		apic_set_isr(vector, apic);
		__apic_update_ppr(apic, &ppr);
	}

	return vector;
}