static inline int stack_guard_page_start(struct vm_area_struct *vma,
					     unsigned long addr)
{
	return (vma->vm_flags & VM_GROWSDOWN) &&
		(vma->vm_start == addr) &&
		!vma_growsdown(vma->vm_prev, addr);
}