static void trace(struct kmem_cache *s, struct page *page, void *object, int alloc)
{
	if (s->flags & SLAB_TRACE) {
		printk(KERN_INFO "STR",
			s->name,
			alloc ? "STR",
			object, page->inuse,
			page->freelist);

		if (!alloc)
			print_section("STR", (void *)object, s->objsize);

		dump_stack();
	}
}