hugetlb_vmtruncate_list(struct rb_root *root, pgoff_t pgoff)
{
	struct vm_area_struct *vma;

	vma_interval_tree_foreach(vma, root, pgoff, ULONG_MAX) {
		unsigned long v_offset;

		
		if (vma->vm_pgoff < pgoff)
			v_offset = (pgoff - vma->vm_pgoff) << PAGE_SHIFT;
		else
			v_offset = 0;

		unmap_hugepage_range(vma, vma->vm_start + v_offset,
				     vma->vm_end, NULL);
	}
}