pgd_t * __init efi_call_phys_prolog(void)
{
	unsigned long vaddr, addr_pgd, addr_p4d, addr_pud;
	pgd_t *save_pgd, *pgd_k, *pgd_efi;
	p4d_t *p4d, *p4d_k, *p4d_efi;
	pud_t *pud;

	int pgd;
	int n_pgds, i, j;

	if (!efi_enabled(EFI_OLD_MEMMAP)) {
		efi_switch_mm(&efi_mm);
		return NULL;
	}

	early_code_mapping_set_exec(1);

	n_pgds = DIV_ROUND_UP((max_pfn << PAGE_SHIFT), PGDIR_SIZE);
	save_pgd = kmalloc_array(n_pgds, sizeof(*save_pgd), GFP_KERNEL);

	
	for (pgd = 0; pgd < n_pgds; pgd++) {
		addr_pgd = (unsigned long)(pgd * PGDIR_SIZE);
		vaddr = (unsigned long)__va(pgd * PGDIR_SIZE);
		pgd_efi = pgd_offset_k(addr_pgd);
		save_pgd[pgd] = *pgd_efi;

		p4d = p4d_alloc(&init_mm, pgd_efi, addr_pgd);
		if (!p4d) {
			pr_err("STR");
			goto out;
		}

		for (i = 0; i < PTRS_PER_P4D; i++) {
			addr_p4d = addr_pgd + i * P4D_SIZE;
			p4d_efi = p4d + p4d_index(addr_p4d);

			pud = pud_alloc(&init_mm, p4d_efi, addr_p4d);
			if (!pud) {
				pr_err("STR");
				goto out;
			}

			for (j = 0; j < PTRS_PER_PUD; j++) {
				addr_pud = addr_p4d + j * PUD_SIZE;

				if (addr_pud > (max_pfn << PAGE_SHIFT))
					break;

				vaddr = (unsigned long)__va(addr_pud);

				pgd_k = pgd_offset_k(vaddr);
				p4d_k = p4d_offset(pgd_k, vaddr);
				pud[j] = *pud_offset(p4d_k, vaddr);
			}
		}
		pgd_offset_k(pgd * PGDIR_SIZE)->pgd &= ~_PAGE_NX;
	}

out:
	__flush_tlb_all();

	return save_pgd;
}