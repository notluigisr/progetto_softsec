static void update_and_free_page(struct hstate *h, struct page *page,
				 bool atomic)
{
	if (!HPageVmemmapOptimized(page) || !atomic) {
		__update_and_free_page(h, page);
		return;
	}

	
	if (llist_add((struct llist_node *)&page->mapping, &hpage_freelist))
		schedule_work(&free_hpage_work);
}