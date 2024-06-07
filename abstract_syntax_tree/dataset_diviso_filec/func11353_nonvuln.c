static void bad_page(struct page *page, const char *reason,
		unsigned long bad_flags)
{
	static unsigned long resume;
	static unsigned long nr_shown;
	static unsigned long nr_unshown;

	
	if (nr_shown == 60) {
		if (time_before(jiffies, resume)) {
			nr_unshown++;
			goto out;
		}
		if (nr_unshown) {
			pr_alert(
			      "STR",
				nr_unshown);
			nr_unshown = 0;
		}
		nr_shown = 0;
	}
	if (nr_shown++ == 0)
		resume = jiffies + 60 * HZ;

	pr_alert("STR",
		current->comm, page_to_pfn(page));
	__dump_page(page, reason);
	bad_flags &= page->flags;
	if (bad_flags)
		pr_alert("STR",
						bad_flags, &bad_flags);
	dump_page_owner(page);

	print_modules();
	dump_stack();
out:
	
	page_mapcount_reset(page); 
	add_taint(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
}