static void touch_pmd(struct vm_area_struct *vma, unsigned long addr,
		pmd_t *pmd)
{
	pmd_t _pmd;

	
	_pmd = pmd_mkyoung(pmd_mkdirty(*pmd));
	if (pmdp_set_access_flags(vma, addr & HPAGE_PMD_MASK,
				pmd, _pmd,  1))
		update_mmu_cache_pmd(vma, addr, pmd);
}