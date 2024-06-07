void dump_mm(const struct mm_struct *mm)
{
	pr_emerg("STR"
#ifdef CONFIG_MMU
		"STR"
#endif
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
#ifdef CONFIG_AIO
		"STR"
#endif
#ifdef CONFIG_MEMCG
		"STR"
#endif
		"STR"
#ifdef CONFIG_MMU_NOTIFIER
		"STR"
#endif
#ifdef CONFIG_NUMA_BALANCING
		"STR"
#endif
		"STR"
		"STR",

		mm, mm->mmap, mm->vmacache_seqnum, mm->task_size,
#ifdef CONFIG_MMU
		mm->get_unmapped_area,
#endif
		mm->mmap_base, mm->mmap_legacy_base, mm->highest_vm_end,
		mm->pgd, atomic_read(&mm->mm_users),
		atomic_read(&mm->mm_count),
		mm_pgtables_bytes(mm),
		mm->map_count,
		mm->hiwater_rss, mm->hiwater_vm, mm->total_vm, mm->locked_vm,
		mm->pinned_vm, mm->data_vm, mm->exec_vm, mm->stack_vm,
		mm->start_code, mm->end_code, mm->start_data, mm->end_data,
		mm->start_brk, mm->brk, mm->start_stack,
		mm->arg_start, mm->arg_end, mm->env_start, mm->env_end,
		mm->binfmt, mm->flags, mm->core_state,
#ifdef CONFIG_AIO
		mm->ioctx_table,
#endif
#ifdef CONFIG_MEMCG
		mm->owner,
#endif
		mm->exe_file,
#ifdef CONFIG_MMU_NOTIFIER
		mm->mmu_notifier_mm,
#endif
#ifdef CONFIG_NUMA_BALANCING
		mm->numa_next_scan, mm->numa_scan_offset, mm->numa_scan_seq,
#endif
		atomic_read(&mm->tlb_flush_pending),
		mm->def_flags, &mm->def_flags
	);
}