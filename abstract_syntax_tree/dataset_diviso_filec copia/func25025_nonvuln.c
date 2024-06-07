int kvm_handle_memory_failure(struct kvm_vcpu *vcpu, int r,
			      struct x86_exception *e)
{
	if (r == X86EMUL_PROPAGATE_FAULT) {
		kvm_inject_emulated_page_fault(vcpu, e);
		return 1;
	}

	
	kvm_prepare_emulation_failure_exit(vcpu);

	return 0;
}