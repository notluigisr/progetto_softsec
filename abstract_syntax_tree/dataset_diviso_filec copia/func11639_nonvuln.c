static int kvm_vcpu_ioctl_x86_set_xsave(struct kvm_vcpu *vcpu,
					struct kvm_xsave *guest_xsave)
{
	if (fpstate_is_confidential(&vcpu->arch.guest_fpu))
		return 0;

	return fpu_copy_uabi_to_guest_fpstate(&vcpu->arch.guest_fpu,
					      guest_xsave->region,
					      supported_xcr0, &vcpu->arch.pkru);
}