static inline pmd_t pmdp_get_and_clear(struct mm_struct *mm, unsigned long addr,
				       pmd_t *pmdp)
{
	pmd_t pmd = native_pmdp_get_and_clear(pmdp);
	pmd_update(mm, addr, pmdp);
	return pmd;
}