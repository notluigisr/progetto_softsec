ext2_xattr_cache_insert(struct buffer_head *bh)
{
	__u32 hash = le32_to_cpu(HDR(bh)->h_hash);
	struct mb_cache_entry *ce;
	int error;

	ce = mb_cache_entry_alloc(ext2_xattr_cache, GFP_NOFS);
	if (!ce)
		return -ENOMEM;
	error = mb_cache_entry_insert(ce, bh->b_bdev, bh->b_blocknr, hash);
	if (error) {
		mb_cache_entry_free(ce);
		if (error == -EBUSY) {
			ea_bdebug(bh, "STR",
				atomic_read(&ext2_xattr_cache->c_entry_count));
			error = 0;
		}
	} else {
		ea_bdebug(bh, "STR", (int)hash,
			  atomic_read(&ext2_xattr_cache->c_entry_count));
		mb_cache_entry_release(ce);
	}
	return error;
}