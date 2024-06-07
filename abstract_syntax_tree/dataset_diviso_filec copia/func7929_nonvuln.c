int follow_pte_pmd(struct mm_struct *mm, unsigned long address,
			     pte_t **ptepp, pmd_t **pmdpp, spinlock_t **ptlp)
{
	int res;

	
	(void) __cond_lock(*ptlp,
			   !(res = __follow_pte_pmd(mm, address, ptepp, pmdpp,
					   ptlp)));
	return res;
}