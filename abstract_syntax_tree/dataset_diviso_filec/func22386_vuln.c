
static __always_inline int __kvm_handle_hva_range(struct kvm *kvm,
						  const struct kvm_hva_range *range)
{
	bool ret = false, locked = false;
	struct kvm_gfn_range gfn_range;
	struct kvm_memory_slot *slot;
	struct kvm_memslots *slots;
	int i, idx;

	if (WARN_ON_ONCE(range->end <= range->start))
		return 0;

	
	if (WARN_ON_ONCE(IS_KVM_NULL_FN(range->on_lock) &&
			 IS_KVM_NULL_FN(range->handler)))
		return 0;

	idx = srcu_read_lock(&kvm->srcu);

	for (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) {
		struct interval_tree_node *node;

		slots = __kvm_memslots(kvm, i);
		kvm_for_each_memslot_in_hva_range(node, slots,
						  range->start, range->end - 1) {
			unsigned long hva_start, hva_end;

			slot = container_of(node, struct kvm_memory_slot, hva_node[slots->node_idx]);
			hva_start = max(range->start, slot->userspace_addr);
			hva_end = min(range->end, slot->userspace_addr +
						  (slot->npages << PAGE_SHIFT));

			
			gfn_range.pte = range->pte;
			gfn_range.may_block = range->may_block;

			
			gfn_range.start = hva_to_gfn_memslot(hva_start, slot);
			gfn_range.end = hva_to_gfn_memslot(hva_end + PAGE_SIZE - 1, slot);
			gfn_range.slot = slot;

			if (!locked) {
				locked = true;
				KVM_MMU_LOCK(kvm);
				if (!IS_KVM_NULL_FN(range->on_lock))
					range->on_lock(kvm, range->start, range->end);
				if (IS_KVM_NULL_FN(range->handler))
					break;
			}
			ret |= range->handler(kvm, &gfn_range);
		}
	}

	if (range->flush_on_ret && ret)
		kvm_flush_remote_tlbs(kvm);

	if (locked)
		KVM_MMU_UNLOCK(kvm);

	srcu_read_unlock(&kvm->srcu, idx);

	
	return (int)ret;