struct page *follow_devmap_pmd(struct vm_area_struct *vma, unsigned long addr,
		pmd_t *pmd, int flags)
{
	unsigned long pfn = pmd_pfn(*pmd);
	struct mm_struct *mm = vma->vm_mm;
	struct dev_pagemap *pgmap;
	struct page *page;

	assert_spin_locked(pmd_lockptr(mm, pmd));

	
	WARN_ONCE(flags & FOLL_COW, "STR");

	if (flags & FOLL_WRITE && !pmd_write(*pmd))
		return NULL;

	if (pmd_present(*pmd) && pmd_devmap(*pmd))
		;
	else
		return NULL;

	if (flags & FOLL_TOUCH)
		touch_pmd(vma, addr, pmd);

	
	if (!(flags & FOLL_GET))
		return ERR_PTR(-EEXIST);

	pfn += (addr & ~PMD_MASK) >> PAGE_SHIFT;
	pgmap = get_dev_pagemap(pfn, NULL);
	if (!pgmap)
		return ERR_PTR(-EFAULT);
	page = pfn_to_page(pfn);
	get_page(page);
	put_dev_pagemap(pgmap);

	return page;
}