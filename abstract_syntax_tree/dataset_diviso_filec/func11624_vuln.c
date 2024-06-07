static int sanity_check_raw_super(struct f2fs_sb_info *sbi,
				struct buffer_head *bh)
{
	struct f2fs_super_block *raw_super = (struct f2fs_super_block *)
					(bh->b_data + F2FS_SUPER_OFFSET);
	struct super_block *sb = sbi->sb;
	unsigned int blocksize;

	if (F2FS_SUPER_MAGIC != le32_to_cpu(raw_super->magic)) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			F2FS_SUPER_MAGIC, le32_to_cpu(raw_super->magic));
		return 1;
	}

	
	if (F2FS_BLKSIZE != PAGE_SIZE) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			PAGE_SIZE);
		return 1;
	}

	
	blocksize = 1 << le32_to_cpu(raw_super->log_blocksize);
	if (blocksize != F2FS_BLKSIZE) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			blocksize);
		return 1;
	}

	
	if (le32_to_cpu(raw_super->log_blocks_per_seg) != 9) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			le32_to_cpu(raw_super->log_blocks_per_seg));
		return 1;
	}

	
	if (le32_to_cpu(raw_super->log_sectorsize) >
				F2FS_MAX_LOG_SECTOR_SIZE ||
		le32_to_cpu(raw_super->log_sectorsize) <
				F2FS_MIN_LOG_SECTOR_SIZE) {
		f2fs_msg(sb, KERN_INFO, "STR",
			le32_to_cpu(raw_super->log_sectorsize));
		return 1;
	}
	if (le32_to_cpu(raw_super->log_sectors_per_block) +
		le32_to_cpu(raw_super->log_sectorsize) !=
			F2FS_MAX_LOG_SECTOR_SIZE) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			le32_to_cpu(raw_super->log_sectors_per_block),
			le32_to_cpu(raw_super->log_sectorsize));
		return 1;
	}

	
	if (le32_to_cpu(raw_super->node_ino) != 1 ||
		le32_to_cpu(raw_super->meta_ino) != 2 ||
		le32_to_cpu(raw_super->root_ino) != 3) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			le32_to_cpu(raw_super->node_ino),
			le32_to_cpu(raw_super->meta_ino),
			le32_to_cpu(raw_super->root_ino));
		return 1;
	}

	
	if (sanity_check_area_boundary(sbi, bh))
		return 1;

	return 0;
}