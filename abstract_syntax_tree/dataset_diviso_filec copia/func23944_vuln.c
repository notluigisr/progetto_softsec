
static void kvm_invalidate_memslot(struct kvm *kvm,
				   struct kvm_memory_slot *old,
				   struct kvm_memory_slot *invalid_slot)
{
	
	kvm_copy_memslot(invalid_slot, old);
	invalid_slot->flags |= KVM_MEMSLOT_INVALID;
	kvm_replace_memslot(kvm, old, invalid_slot);

	
	kvm_swap_active_memslots(kvm, old->as_id);

	
	kvm_arch_flush_shadow_memslot(kvm, old);

	
	mutex_lock(&kvm->slots_arch_lock);

	
	old->arch = invalid_slot->arch;