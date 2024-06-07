static bool nested_vmx_exit_handled_vmcs_access(struct kvm_vcpu *vcpu,
	struct vmcs12 *vmcs12, gpa_t bitmap)
{
	u32 vmx_instruction_info;
	unsigned long field;
	u8 b;

	if (!nested_cpu_has_shadow_vmcs(vmcs12))
		return true;

	
	vmx_instruction_info = vmcs_read32(VMX_INSTRUCTION_INFO);
	field = kvm_register_read(vcpu, (((vmx_instruction_info) >> 28) & 0xf));

	
	if (field >> 15)
		return true;

	if (kvm_vcpu_read_guest(vcpu, bitmap + field/8, &b, 1))
		return true;

	return 1 & (b >> (field & 7));
}