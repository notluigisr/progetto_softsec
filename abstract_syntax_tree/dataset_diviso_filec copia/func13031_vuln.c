static int ext4_get_block_write(struct inode *inode, sector_t iblock,
		   struct buffer_head *bh_result, int create)
{
	handle_t *handle = NULL;
	int ret = 0;
	unsigned max_blocks = bh_result->b_size >> inode->i_blkbits;
	int dio_credits;

	ext4_debug("STR",
		   inode->i_ino, create);
	
	create = EXT4_GET_BLOCKS_IO_CREATE_EXT;

	if (max_blocks > DIO_MAX_BLOCKS)
		max_blocks = DIO_MAX_BLOCKS;
	dio_credits = ext4_chunk_trans_blocks(inode, max_blocks);
	handle = ext4_journal_start(inode, dio_credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out;
	}
	ret = ext4_get_blocks(handle, inode, iblock, max_blocks, bh_result,
			      create);
	if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		ret = 0;
	}
	ext4_journal_stop(handle);
out:
	return ret;
}