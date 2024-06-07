void hash_preload(struct mm_struct *mm, unsigned long ea,
		  unsigned long access, unsigned long trap)
{
	unsigned long vsid;
	void *pgdir;
	pte_t *ptep;
	cpumask_t mask;
	unsigned long flags;
	int local = 0;

	
	if (unlikely(in_hugepage_area(mm->context, ea)))
		return;

	DBG_LOW("STR"
		"STR", mm, mm->pgd, ea, access, trap);

	
	pgdir = mm->pgd;
	if (pgdir == NULL)
		return;
	ptep = find_linux_pte(pgdir, ea);
	if (!ptep)
		return;
	vsid = get_vsid(mm->context.id, ea);

	
	local_irq_save(flags);
	mask = cpumask_of_cpu(smp_processor_id());
	if (cpus_equal(mm->cpu_vm_mask, mask))
		local = 1;
#ifndef CONFIG_PPC_64K_PAGES
	__hash_page_4K(ea, access, vsid, ptep, trap, local);
#else
	if (mmu_ci_restrictions) {
		
		if (mm->context.user_psize == MMU_PAGE_64K &&
		    (pte_val(*ptep) & _PAGE_NO_CACHE)) {
			mm->context.user_psize = MMU_PAGE_4K;
			mm->context.sllp = SLB_VSID_USER |
				mmu_psize_defs[MMU_PAGE_4K].sllp;
			get_paca()->context = mm->context;
			slb_flush_and_rebolt();
#ifdef CONFIG_SPE_BASE
			spu_flush_all_slbs(mm);
#endif
		}
	}
	if (mm->context.user_psize == MMU_PAGE_64K)
		__hash_page_64K(ea, access, vsid, ptep, trap, local);
	else
		__hash_page_4K(ea, access, vsid, ptep, trap, local);
#endif 
	local_irq_restore(flags);
}