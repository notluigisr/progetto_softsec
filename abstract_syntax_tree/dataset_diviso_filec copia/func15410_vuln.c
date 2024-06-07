struct page *cma_alloc(struct cma *cma, unsigned int count, unsigned int align)
{
	unsigned long mask, offset, pfn, start = 0;
	unsigned long bitmap_maxno, bitmap_no, bitmap_count;
	struct page *page = NULL;
	int ret;

	if (!cma || !cma->count)
		return NULL;

	pr_debug("STR", __func__, (void *)cma,
		 count, align);

	if (!count)
		return NULL;

	mask = cma_bitmap_aligned_mask(cma, align);
	offset = cma_bitmap_aligned_offset(cma, align);
	bitmap_maxno = cma_bitmap_maxno(cma);
	bitmap_count = cma_bitmap_pages_to_bits(cma, count);

	for (;;) {
		mutex_lock(&cma->lock);
		bitmap_no = bitmap_find_next_zero_area_off(cma->bitmap,
				bitmap_maxno, start, bitmap_count, mask,
				offset);
		if (bitmap_no >= bitmap_maxno) {
			mutex_unlock(&cma->lock);
			break;
		}
		bitmap_set(cma->bitmap, bitmap_no, bitmap_count);
		
		mutex_unlock(&cma->lock);

		pfn = cma->base_pfn + (bitmap_no << cma->order_per_bit);
		mutex_lock(&cma_mutex);
		ret = alloc_contig_range(pfn, pfn + count, MIGRATE_CMA);
		mutex_unlock(&cma_mutex);
		if (ret == 0) {
			page = pfn_to_page(pfn);
			break;
		}

		cma_clear_bitmap(cma, pfn, count);
		if (ret != -EBUSY)
			break;

		pr_debug("STR",
			 __func__, pfn_to_page(pfn));
		
		start = bitmap_no + mask + 1;
	}

	trace_cma_alloc(page ? pfn : -1UL, page, count, align);

	pr_debug("STR", __func__, page);
	return page;
}