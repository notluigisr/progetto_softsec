static int sanity_check_raw_super(struct super_block *sb,
			struct f2fs_super_block *raw_super)
{
	unsigned int blocksize;

	if (F2FS_SUPER_MAGIC != le32_to_cpu(raw_super->magic)) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			F2FS_SUPER_MAGIC, le32_to_cpu(raw_super->magic));
		return 1;
	}

	
	if (F2FS_BLKSIZE != PAGE_CACHE_SIZE) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			PAGE_CACHE_SIZE);
		return 1;
	}

	
	blocksize = 1 << le32_to_cpu(raw_super->log_blocksize);
	if (blocksize != F2FS_BLKSIZE) {
		f2fs_msg(sb, KERN_INFO,
			"STR",
			blocksize);
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
	return 0;
}