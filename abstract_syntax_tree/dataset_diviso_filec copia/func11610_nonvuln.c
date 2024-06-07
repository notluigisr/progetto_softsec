void unpin_user_pages(struct page **pages, unsigned long npages)
{
	unsigned long index;

	
	for (index = 0; index < npages; index++)
		unpin_user_page(pages[index]);
}