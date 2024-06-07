int f2fs_release_page(struct page *page, gfp_t wait)
{
	
	if (PageDirty(page))
		return 0;

	
	if (IS_ATOMIC_WRITTEN_PAGE(page))
		return 0;

	clear_cold_data(page);
	f2fs_clear_page_private(page);
	return 1;
}