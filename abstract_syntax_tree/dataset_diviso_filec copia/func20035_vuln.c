int expand_upwards(struct vm_area_struct *vma, unsigned long address)
{
	struct mm_struct *mm = vma->vm_mm;
	int error = 0;

	if (!(vma->vm_flags & VM_GROWSUP))
		return -EFAULT;

	
	if (address < PAGE_ALIGN(address+4))
		address = PAGE_ALIGN(address+4);
	else
		return -ENOMEM;

	
	if (unlikely(anon_vma_prepare(vma)))
		return -ENOMEM;

	
	anon_vma_lock_write(vma->anon_vma);

	
	if (address > vma->vm_end) {
		unsigned long size, grow;

		size = address - vma->vm_start;
		grow = (address - vma->vm_end) >> PAGE_SHIFT;

		error = -ENOMEM;
		if (vma->vm_pgoff + (size >> PAGE_SHIFT) >= vma->vm_pgoff) {
			error = acct_stack_growth(vma, size, grow);
			if (!error) {
				
				spin_lock(&mm->page_table_lock);
				if (vma->vm_flags & VM_LOCKED)
					mm->locked_vm += grow;
				vm_stat_account(mm, vma->vm_flags, grow);
				anon_vma_interval_tree_pre_update_vma(vma);
				vma->vm_end = address;
				anon_vma_interval_tree_post_update_vma(vma);
				if (vma->vm_next)
					vma_gap_update(vma->vm_next);
				else
					mm->highest_vm_end = address;
				spin_unlock(&mm->page_table_lock);

				perf_event_mmap(vma);
			}
		}
	}
	anon_vma_unlock_write(vma->anon_vma);
	khugepaged_enter_vma_merge(vma, vma->vm_flags);
	validate_mm(mm);
	return error;
}