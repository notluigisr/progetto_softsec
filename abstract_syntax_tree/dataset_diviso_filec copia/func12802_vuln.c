static inline int vma_growsdown(struct vm_area_struct *vma, unsigned long addr)
{
	return vma && (vma->vm_end == addr) && (vma->vm_flags & VM_GROWSDOWN);
}