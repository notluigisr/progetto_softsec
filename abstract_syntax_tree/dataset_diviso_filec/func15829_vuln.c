static inline int stack_guard_page_end(struct vm_area_struct *vma,
					   unsigned long addr)
{
	return (vma->vm_flags & VM_GROWSUP) &&
		(vma->vm_end == addr) &&
		!vma_growsup(vma->vm_next, addr);
}