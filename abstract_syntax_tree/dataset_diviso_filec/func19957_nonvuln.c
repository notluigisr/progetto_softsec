static int ext4_da_write_end(struct file *file,
			     struct address_space *mapping,
			     loff_t pos, unsigned len, unsigned copied,
			     struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	int ret = 0, ret2;
	handle_t *handle = ext4_journal_current_handle();
	loff_t new_i_size;
	unsigned long start, end;
	int write_mode = (int)(unsigned long)fsdata;

	if (write_mode == FALL_BACK_TO_NONDELALLOC) {
		if (ext4_should_order_data(inode)) {
			return ext4_ordered_write_end(file, mapping, pos,
					len, copied, page, fsdata);
		} else if (ext4_should_writeback_data(inode)) {
			return ext4_writeback_write_end(file, mapping, pos,
					len, copied, page, fsdata);
		} else {
			BUG();
		}
	}

	trace_ext4_da_write_end(inode, pos, len, copied);
	start = pos & (PAGE_CACHE_SIZE - 1);
	end = start + copied - 1;

	

	new_i_size = pos + copied;
	if (new_i_size > EXT4_I(inode)->i_disksize) {
		if (ext4_da_should_update_i_disksize(page, end)) {
			down_write(&EXT4_I(inode)->i_data_sem);
			if (new_i_size > EXT4_I(inode)->i_disksize) {
				
				if (ext4_should_order_data(inode))
					ret = ext4_jbd2_file_inode(handle,
								   inode);

				EXT4_I(inode)->i_disksize = new_i_size;
			}
			up_write(&EXT4_I(inode)->i_data_sem);
			
			ext4_mark_inode_dirty(handle, inode);
		}
	}
	ret2 = generic_write_end(file, mapping, pos, len, copied,
							page, fsdata);
	copied = ret2;
	if (ret2 < 0)
		ret = ret2;
	ret2 = ext4_journal_stop(handle);
	if (!ret)
		ret = ret2;

	return ret ? ret : copied;
}