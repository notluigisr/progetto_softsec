static void sev_flush_encrypted_page(struct kvm_vcpu *vcpu, void *va)
{
	int asid = to_kvm_svm(vcpu->kvm)->sev_info.asid;

	
	unsigned long addr = (unsigned long)va;

	
	if (boot_cpu_has(X86_FEATURE_SME_COHERENT)) {
		clflush_cache_range(va, PAGE_SIZE);
		return;
	}

	
	if (WARN_ON_ONCE(wrmsrl_safe(MSR_AMD64_VM_PAGE_FLUSH, addr | asid)))
		goto do_wbinvd;

	return;

do_wbinvd:
	wbinvd_on_all_cpus();
}