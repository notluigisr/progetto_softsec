static void frob_text(const struct module_layout *layout,
		      int (*set_memory)(unsigned long start, int num_pages))
{
	BUG_ON((unsigned long)layout->base & (PAGE_SIZE-1));
	BUG_ON((unsigned long)layout->text_size & (PAGE_SIZE-1));
	set_memory((unsigned long)layout->base,
		   layout->text_size >> PAGE_SHIFT);
}