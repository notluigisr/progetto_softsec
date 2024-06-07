static void memcpy_to_page(struct page *page, size_t offset, const char *from, size_t len)
{
	char *to = kmap_atomic(page);
	memcpy(to + offset, from, len);
	kunmap_atomic(to);
}