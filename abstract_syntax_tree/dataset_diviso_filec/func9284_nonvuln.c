bool __tlb_remove_page_size(struct mmu_gather *tlb, struct page *page, int page_size)
{
	struct mmu_gather_batch *batch;

	VM_BUG_ON(!tlb->end);
	VM_WARN_ON(tlb->page_size != page_size);

	batch = tlb->active;
	
	batch->pages[batch->nr++] = page;
	if (batch->nr == batch->max) {
		if (!tlb_next_batch(tlb))
			return true;
		batch = tlb->active;
	}
	VM_BUG_ON_PAGE(batch->nr > batch->max, page);

	return false;
}