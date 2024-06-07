static int nested_vmx_check_vmptr(struct kvm_vcpu *vcpu, int exit_reason,
				  gpa_t *vmpointer)
{
	gva_t gva;
	gpa_t vmptr;
	struct x86_exception e;
	struct page *page;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int maxphyaddr = cpuid_maxphyaddr(vcpu);

	if (get_vmx_mem_address(vcpu, vmcs_readl(EXIT_QUALIFICATION),
			vmcs_read32(VMX_INSTRUCTION_INFO), &gva))
		return 1;

	if (kvm_read_guest_virt(&vcpu->arch.emulate_ctxt, gva, &vmptr,
				sizeof(vmptr), &e)) {
		kvm_inject_page_fault(vcpu, &e);
		return 1;
	}

	switch (exit_reason) {
	case EXIT_REASON_VMON:
		
		if (!PAGE_ALIGNED(vmptr) || (vmptr >> maxphyaddr)) {
			nested_vmx_failInvalid(vcpu);
			skip_emulated_instruction(vcpu);
			return 1;
		}

		page = nested_get_page(vcpu, vmptr);
		if (page == NULL ||
		    *(u32 *)kmap(page) != VMCS12_REVISION) {
			nested_vmx_failInvalid(vcpu);
			kunmap(page);
			skip_emulated_instruction(vcpu);
			return 1;
		}
		kunmap(page);
		vmx->nested.vmxon_ptr = vmptr;
		break;
	case EXIT_REASON_VMCLEAR:
		if (!PAGE_ALIGNED(vmptr) || (vmptr >> maxphyaddr)) {
			nested_vmx_failValid(vcpu,
					     VMXERR_VMCLEAR_INVALID_ADDRESS);
			skip_emulated_instruction(vcpu);
			return 1;
		}

		if (vmptr == vmx->nested.vmxon_ptr) {
			nested_vmx_failValid(vcpu,
					     VMXERR_VMCLEAR_VMXON_POINTER);
			skip_emulated_instruction(vcpu);
			return 1;
		}
		break;
	case EXIT_REASON_VMPTRLD:
		if (!PAGE_ALIGNED(vmptr) || (vmptr >> maxphyaddr)) {
			nested_vmx_failValid(vcpu,
					     VMXERR_VMPTRLD_INVALID_ADDRESS);
			skip_emulated_instruction(vcpu);
			return 1;
		}

		if (vmptr == vmx->nested.vmxon_ptr) {
			nested_vmx_failValid(vcpu,
					     VMXERR_VMCLEAR_VMXON_POINTER);
			skip_emulated_instruction(vcpu);
			return 1;
		}
		break;
	default:
		return 1; 
	}

	if (vmpointer)
		*vmpointer = vmptr;
	return 0;
}