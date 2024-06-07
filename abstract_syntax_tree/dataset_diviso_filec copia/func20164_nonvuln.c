static int ext4_set_page_dirty(struct page *page)
{
	WARN_ON_ONCE(!PageLocked(page) && !PageDirty(page));
	WARN_ON_ONCE(!page_has_buffers(page));
	return __set_page_dirty_buffers(page);
}