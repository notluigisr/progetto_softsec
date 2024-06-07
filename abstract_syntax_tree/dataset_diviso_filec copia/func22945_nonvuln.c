swiotlb_late_init_with_default_size(size_t default_size)
{
	unsigned long nslabs =
		ALIGN(default_size >> IO_TLB_SHIFT, IO_TLB_SEGSIZE);
	unsigned long bytes;
	unsigned char *vstart = NULL;
	unsigned int order;
	int rc = 0;

	if (swiotlb_force == SWIOTLB_NO_FORCE)
		return 0;

	
	order = get_order(nslabs << IO_TLB_SHIFT);
	nslabs = SLABS_PER_PAGE << order;
	bytes = nslabs << IO_TLB_SHIFT;

	while ((SLABS_PER_PAGE << order) > IO_TLB_MIN_SLABS) {
		vstart = (void *)__get_free_pages(GFP_DMA | __GFP_NOWARN,
						  order);
		if (vstart)
			break;
		order--;
	}

	if (!vstart)
		return -ENOMEM;

	if (order != get_order(bytes)) {
		pr_warn("STR",
			(PAGE_SIZE << order) >> 20);
		nslabs = SLABS_PER_PAGE << order;
	}
	rc = swiotlb_late_init_with_tbl(vstart, nslabs);
	if (rc)
		free_pages((unsigned long)vstart, order);

	return rc;
}