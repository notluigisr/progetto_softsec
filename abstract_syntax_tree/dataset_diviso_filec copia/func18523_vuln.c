static inline void vma_adjust_trans_huge(struct vm_area_struct *vma,
					 unsigned long start,
					 unsigned long end,
					 long adjust_next)
{
	if (!vma->anon_vma || vma->vm_ops || vma->vm_file)
		return;
	__vma_adjust_trans_huge(vma, start, end, adjust_next);
}