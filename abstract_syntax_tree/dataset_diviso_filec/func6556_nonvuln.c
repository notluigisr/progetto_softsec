static inline void kvm_vcpu_flush_tlb_current(struct kvm_vcpu *vcpu)
{
	++vcpu->stat.tlb_flush;
	static_call(kvm_x86_flush_tlb_current)(vcpu);
}