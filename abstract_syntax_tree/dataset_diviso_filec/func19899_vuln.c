static inline int vma_growsup(struct vm_area_struct *vma, unsigned long addr)
{
	return vma && (vma->vm_start == addr) && (vma->vm_flags & VM_GROWSUP);
}