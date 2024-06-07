void free_transhuge_page(struct page *page)
{
	struct pglist_data *pgdata = NODE_DATA(page_to_nid(page));
	unsigned long flags;

	spin_lock_irqsave(&pgdata->split_queue_lock, flags);
	if (!list_empty(page_deferred_list(page))) {
		pgdata->split_queue_len--;
		list_del(page_deferred_list(page));
	}
	spin_unlock_irqrestore(&pgdata->split_queue_lock, flags);
	free_compound_page(page);
}