ext4_read_block_bitmap_nowait(struct super_block *sb, ext4_group_t block_group)
{
	struct ext4_group_desc *desc;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct buffer_head *bh;
	ext4_fsblk_t bitmap_blk;
	int err;

	desc = ext4_get_group_desc(sb, block_group, NULL);
	if (!desc)
		return ERR_PTR(-EFSCORRUPTED);
	bitmap_blk = ext4_block_bitmap(sb, desc);
	if ((bitmap_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (bitmap_blk >= ext4_blocks_count(sbi->s_es))) {
		ext4_error(sb, "STR"
			   "STR", bitmap_blk, block_group);
		ext4_mark_group_bitmap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		return ERR_PTR(-EFSCORRUPTED);
	}
	bh = sb_getblk(sb, bitmap_blk);
	if (unlikely(!bh)) {
		ext4_error(sb, "STR"
			   "STR",
			   block_group, bitmap_blk);
		return ERR_PTR(-ENOMEM);
	}

	if (bitmap_uptodate(bh))
		goto verify;

	lock_buffer(bh);
	if (bitmap_uptodate(bh)) {
		unlock_buffer(bh);
		goto verify;
	}
	ext4_lock_group(sb, block_group);
	if (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
		err = ext4_init_block_bitmap(sb, bh, block_group, desc);
		set_bitmap_uptodate(bh);
		set_buffer_uptodate(bh);
		set_buffer_verified(bh);
		ext4_unlock_group(sb, block_group);
		unlock_buffer(bh);
		if (err) {
			ext4_error(sb, "STR"
				   "STR", block_group, err);
			goto out;
		}
		goto verify;
	}
	ext4_unlock_group(sb, block_group);
	if (buffer_uptodate(bh)) {
		
		set_bitmap_uptodate(bh);
		unlock_buffer(bh);
		goto verify;
	}
	
	set_buffer_new(bh);
	trace_ext4_read_block_bitmap_load(sb, block_group);
	bh->b_end_io = ext4_end_bitmap_read;
	get_bh(bh);
	submit_bh(REQ_OP_READ, REQ_META | REQ_PRIO, bh);
	return bh;
verify:
	err = ext4_validate_block_bitmap(sb, desc, block_group, bh);
	if (err)
		goto out;
	return bh;
out:
	put_bh(bh);
	return ERR_PTR(err);
}