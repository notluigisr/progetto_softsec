static inline int check_stack_guard_page(struct vm_area_struct *vma, unsigned long address)
{
	address &= PAGE_MASK;
	if ((vma->vm_flags & VM_GROWSDOWN) && address == vma->vm_start) {
		struct vm_area_struct *prev = vma->vm_prev;

		
		if (prev && prev->vm_end == address)
			return prev->vm_flags & VM_GROWSDOWN ? 0 : -ENOMEM;

		return expand_downwards(vma, address - PAGE_SIZE);
	}
	if ((vma->vm_flags & VM_GROWSUP) && address + PAGE_SIZE == vma->vm_end) {
		struct vm_area_struct *next = vma->vm_next;

		
		if (next && next->vm_start == address + PAGE_SIZE)
			return next->vm_flags & VM_GROWSUP ? 0 : -ENOMEM;

		return expand_upwards(vma, address + PAGE_SIZE);
	}
	return 0;
}