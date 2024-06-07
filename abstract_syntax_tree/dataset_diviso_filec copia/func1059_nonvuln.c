vmcs12_guest_cr4(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12)
{
	return
		(vmcs_readl(GUEST_CR4) & vcpu->arch.cr4_guest_owned_bits) |
		(vmcs12->guest_cr4 & vmcs12->cr4_guest_host_mask) |
		(vmcs_readl(CR4_READ_SHADOW) & ~(vmcs12->cr4_guest_host_mask |
			vcpu->arch.cr4_guest_owned_bits));
}