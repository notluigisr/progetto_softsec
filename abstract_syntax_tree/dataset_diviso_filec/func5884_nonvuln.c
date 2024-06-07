static inline struct kvm_memslots *kvm_memslots(struct kvm *kvm)
{
	return rcu_dereference_check(kvm->memslots,
			srcu_read_lock_held(&kvm->srcu)
			|| lockdep_is_held(&kvm->slots_lock));
}