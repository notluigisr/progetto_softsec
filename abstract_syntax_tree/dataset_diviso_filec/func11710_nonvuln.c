void __khugepaged_exit(struct mm_struct *mm)
{
	struct mm_slot *mm_slot;
	int free = 0;

	spin_lock(&khugepaged_mm_lock);
	mm_slot = get_mm_slot(mm);
	if (mm_slot && khugepaged_scan.mm_slot != mm_slot) {
		hlist_del(&mm_slot->hash);
		list_del(&mm_slot->mm_node);
		free = 1;
	}

	if (free) {
		spin_unlock(&khugepaged_mm_lock);
		clear_bit(MMF_VM_HUGEPAGE, &mm->flags);
		free_mm_slot(mm_slot);
		mmdrop(mm);
	} else if (mm_slot) {
		spin_unlock(&khugepaged_mm_lock);
		
		down_write(&mm->mmap_sem);
		up_write(&mm->mmap_sem);
	} else
		spin_unlock(&khugepaged_mm_lock);
}