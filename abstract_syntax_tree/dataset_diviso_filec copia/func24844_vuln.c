int __get_user_pages_fast(unsigned long start, int nr_pages, int write,
			  struct page **pages)
{
	unsigned long len, end;
	unsigned long flags;
	int nr_pinned = 0;
	
	unsigned int gup_flags = FOLL_GET;

	if (write)
		gup_flags |= FOLL_WRITE;

	start = untagged_addr(start) & PAGE_MASK;
	len = (unsigned long) nr_pages << PAGE_SHIFT;
	end = start + len;

	if (end <= start)
		return 0;
	if (unlikely(!access_ok((void __user *)start, len)))
		return 0;

	

	if (IS_ENABLED(CONFIG_HAVE_FAST_GUP) &&
	    gup_fast_permitted(start, end)) {
		local_irq_save(flags);
		gup_pgd_range(start, end, gup_flags, pages, &nr_pinned);
		local_irq_restore(flags);
	}

	return nr_pinned;
}