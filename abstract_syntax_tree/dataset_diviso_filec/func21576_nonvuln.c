
static void kvm_create_memslot(struct kvm *kvm,
			       struct kvm_memory_slot *new)
{
	
	kvm_replace_memslot(kvm, NULL, new);
	kvm_activate_memslot(kvm, NULL, new);