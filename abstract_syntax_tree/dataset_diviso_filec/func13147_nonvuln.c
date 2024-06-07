xfs_iozero(
	struct xfs_inode	*ip,	
	loff_t			pos,	
	size_t			count)	
{
	struct page		*page;
	struct address_space	*mapping;
	int			status = 0;


	mapping = VFS_I(ip)->i_mapping;
	do {
		unsigned offset, bytes;
		void *fsdata;

		offset = (pos & (PAGE_CACHE_SIZE -1)); 
		bytes = PAGE_CACHE_SIZE - offset;
		if (bytes > count)
			bytes = count;

		if (IS_DAX(VFS_I(ip))) {
			status = dax_zero_page_range(VFS_I(ip), pos, bytes,
						     xfs_get_blocks_direct);
			if (status)
				break;
		} else {
			status = pagecache_write_begin(NULL, mapping, pos, bytes,
						AOP_FLAG_UNINTERRUPTIBLE,
						&page, &fsdata);
			if (status)
				break;

			zero_user(page, offset, bytes);

			status = pagecache_write_end(NULL, mapping, pos, bytes,
						bytes, page, fsdata);
			WARN_ON(status <= 0); 
			status = 0;
		}
		pos += bytes;
		count -= bytes;
	} while (count);

	return status;
}