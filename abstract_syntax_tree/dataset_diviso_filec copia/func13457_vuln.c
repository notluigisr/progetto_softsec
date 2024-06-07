static void touch_pud(struct vm_area_struct *vma, unsigned long addr,
		pud_t *pud)
{
	pud_t _pud;

	
	_pud = pud_mkyoung(pud_mkdirty(*pud));
	if (pudp_set_access_flags(vma, addr & HPAGE_PUD_MASK,
				pud, _pud,  1))
		update_mmu_cache_pud(vma, addr, pud);
}