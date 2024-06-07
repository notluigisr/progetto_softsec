void vma_adjust_trans_huge(struct vm_area_struct *vma,
			     unsigned long start,
			     unsigned long end,
			     long adjust_next)
{
	
	if (start & ~HPAGE_PMD_MASK &&
	    (start & HPAGE_PMD_MASK) >= vma->vm_start &&
	    (start & HPAGE_PMD_MASK) + HPAGE_PMD_SIZE <= vma->vm_end)
		split_huge_pmd_address(vma, start, false, NULL);

	
	if (end & ~HPAGE_PMD_MASK &&
	    (end & HPAGE_PMD_MASK) >= vma->vm_start &&
	    (end & HPAGE_PMD_MASK) + HPAGE_PMD_SIZE <= vma->vm_end)
		split_huge_pmd_address(vma, end, false, NULL);

	
	if (adjust_next > 0) {
		struct vm_area_struct *next = vma->vm_next;
		unsigned long nstart = next->vm_start;
		nstart += adjust_next << PAGE_SHIFT;
		if (nstart & ~HPAGE_PMD_MASK &&
		    (nstart & HPAGE_PMD_MASK) >= next->vm_start &&
		    (nstart & HPAGE_PMD_MASK) + HPAGE_PMD_SIZE <= next->vm_end)
			split_huge_pmd_address(next, nstart, false, NULL);
	}
}