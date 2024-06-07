void __split_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long address, bool freeze, struct page *page)
{
	spinlock_t *ptl;
	struct mmu_notifier_range range;

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address & HPAGE_PMD_MASK,
				(address & HPAGE_PMD_MASK) + HPAGE_PMD_SIZE);
	mmu_notifier_invalidate_range_start(&range);
	ptl = pmd_lock(vma->vm_mm, pmd);

	
	VM_BUG_ON(freeze && !page);
	if (page && page != pmd_page(*pmd))
	        goto out;

	if (pmd_trans_huge(*pmd)) {
		page = pmd_page(*pmd);
		if (PageMlocked(page))
			clear_page_mlock(page);
	} else if (!(pmd_devmap(*pmd) || is_pmd_migration_entry(*pmd)))
		goto out;
	__split_huge_pmd_locked(vma, pmd, range.start, freeze);
out:
	spin_unlock(ptl);
	
	mmu_notifier_invalidate_range_only_end(&range);
}