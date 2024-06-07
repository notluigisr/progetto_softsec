static inline int ext4_should_writeback_data(struct inode *inode)
{
	if (!S_ISREG(inode->i_mode))
		return 0;
	if (EXT4_JOURNAL(inode) == NULL)
		return 1;
	if (EXT4_I(inode)->i_flags & EXT4_JOURNAL_DATA_FL)
		return 0;
	if (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_WRITEBACK_DATA)
		return 1;
	return 0;
}