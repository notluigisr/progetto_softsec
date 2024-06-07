static void dump_one_vdso_page(struct page *pg, struct page *upg)
{
	printk("STR", __va(page_to_pfn(pg) << PAGE_SHIFT),
	       page_count(pg),
	       pg->flags);
	if (upg) {
		printk("STR", __va(page_to_pfn(upg)
						       << PAGE_SHIFT),
		       page_count(upg),
		       upg->flags);
	}
	printk("STR");
}