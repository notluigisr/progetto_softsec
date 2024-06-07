int udf_expand_file_adinicb(struct inode *inode)
{
	struct page *page;
	char *kaddr;
	struct udf_inode_info *iinfo = UDF_I(inode);
	int err;
	struct writeback_control udf_wbc = {
		.sync_mode = WB_SYNC_NONE,
		.nr_to_write = 1,
	};

	WARN_ON_ONCE(!inode_is_locked(inode));
	if (!iinfo->i_lenAlloc) {
		if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
		else
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
		
		inode->i_data.a_ops = &udf_aops;
		up_write(&iinfo->i_data_sem);
		mark_inode_dirty(inode);
		return 0;
	}
	
	up_write(&iinfo->i_data_sem);

	page = find_or_create_page(inode->i_mapping, 0, GFP_NOFS);
	if (!page)
		return -ENOMEM;

	if (!PageUptodate(page)) {
		kaddr = kmap_atomic(page);
		memset(kaddr + iinfo->i_lenAlloc, 0x00,
		       PAGE_SIZE - iinfo->i_lenAlloc);
		memcpy(kaddr, iinfo->i_data + iinfo->i_lenEAttr,
			iinfo->i_lenAlloc);
		flush_dcache_page(page);
		SetPageUptodate(page);
		kunmap_atomic(kaddr);
	}
	down_write(&iinfo->i_data_sem);
	memset(iinfo->i_data + iinfo->i_lenEAttr, 0x00,
	       iinfo->i_lenAlloc);
	iinfo->i_lenAlloc = 0;
	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
	else
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
	
	inode->i_data.a_ops = &udf_aops;
	up_write(&iinfo->i_data_sem);
	err = inode->i_data.a_ops->writepage(page, &udf_wbc);
	if (err) {
		
		lock_page(page);
		down_write(&iinfo->i_data_sem);
		kaddr = kmap_atomic(page);
		memcpy(iinfo->i_data + iinfo->i_lenEAttr, kaddr, inode->i_size);
		kunmap_atomic(kaddr);
		unlock_page(page);
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
		inode->i_data.a_ops = &udf_adinicb_aops;
		up_write(&iinfo->i_data_sem);
	}
	put_page(page);
	mark_inode_dirty(inode);

	return err;
}