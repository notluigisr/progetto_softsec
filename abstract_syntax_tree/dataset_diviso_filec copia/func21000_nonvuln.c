void kvm_arch_destroy_vm(struct kvm *kvm)
{
	if (current->mm == kvm->mm) {
		
		mutex_lock(&kvm->slots_lock);
		__x86_set_memory_region(kvm, APIC_ACCESS_PAGE_PRIVATE_MEMSLOT,
					0, 0);
		__x86_set_memory_region(kvm, IDENTITY_PAGETABLE_PRIVATE_MEMSLOT,
					0, 0);
		__x86_set_memory_region(kvm, TSS_PRIVATE_MEMSLOT, 0, 0);
		mutex_unlock(&kvm->slots_lock);
	}
	static_call_cond(kvm_x86_vm_destroy)(kvm);
	kvm_free_msr_filter(srcu_dereference_check(kvm->arch.msr_filter, &kvm->srcu, 1));
	kvm_pic_destroy(kvm);
	kvm_ioapic_destroy(kvm);
	kvm_free_vcpus(kvm);
	kvfree(rcu_dereference_check(kvm->arch.apic_map, 1));
	kfree(srcu_dereference_check(kvm->arch.pmu_event_filter, &kvm->srcu, 1));
	kvm_mmu_uninit_vm(kvm);
	kvm_page_track_cleanup(kvm);
	kvm_xen_destroy_vm(kvm);
	kvm_hv_destroy_vm(kvm);
}