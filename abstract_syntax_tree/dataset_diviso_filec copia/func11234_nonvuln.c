void __remove_from_page_cache(struct page *page)
{
	struct address_space *mapping = page->mapping;

	mem_cgroup_uncharge_cache_page(page);
	radix_tree_delete(&mapping->page_tree, page->index);
	page->mapping = NULL;
	mapping->nrpages--;
	__dec_zone_page_state(page, NR_FILE_PAGES);
	BUG_ON(page_mapped(page));

	
	if (PageDirty(page) && mapping_cap_account_dirty(mapping)) {
		dec_zone_page_state(page, NR_FILE_DIRTY);
		dec_bdi_stat(mapping->backing_dev_info, BDI_RECLAIMABLE);
	}
}