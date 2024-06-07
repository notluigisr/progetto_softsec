static int __init hugetlb_init(void)
{
	
	if (HPAGE_SHIFT == 0)
		return 0;

	if (!size_to_hstate(default_hstate_size)) {
		default_hstate_size = HPAGE_SIZE;
		if (!size_to_hstate(default_hstate_size))
			hugetlb_add_hstate(HUGETLB_PAGE_ORDER);
	}
	default_hstate_idx = size_to_hstate(default_hstate_size) - hstates;
	if (default_hstate_max_huge_pages)
		default_hstate.max_huge_pages = default_hstate_max_huge_pages;

	hugetlb_init_hstates();

	gather_bootmem_prealloc();

	report_hugepages();

	hugetlb_sysfs_init();

	hugetlb_register_all_nodes();

	return 0;
}