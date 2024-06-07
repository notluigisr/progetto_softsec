static void migrate_page_copy(struct page *newpage, struct page *page)
{
	copy_highpage(newpage, page);

	if (PageError(page))
		SetPageError(newpage);
	if (PageReferenced(page))
		SetPageReferenced(newpage);
	if (PageUptodate(page))
		SetPageUptodate(newpage);
	if (PageActive(page))
		SetPageActive(newpage);
	if (PageChecked(page))
		SetPageChecked(newpage);
	if (PageMappedToDisk(page))
		SetPageMappedToDisk(newpage);

	if (PageDirty(page)) {
		clear_page_dirty_for_io(page);
		
		__set_page_dirty_nobuffers(newpage);
 	}

#ifdef CONFIG_SWAP
	ClearPageSwapCache(page);
#endif
	ClearPageActive(page);
	ClearPagePrivate(page);
	set_page_private(page, 0);
	page->mapping = NULL;

	
	if (PageWriteback(newpage))
		end_page_writeback(newpage);
}