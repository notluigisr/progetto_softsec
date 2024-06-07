static void object_err(struct kmem_cache *s, struct page *page,
			u8 *object, char *reason)
{
	slab_bug(s, "STR", reason);
	print_trailer(s, page, object);
}