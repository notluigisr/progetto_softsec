static bool ext4_should_enable_dax(struct inode *inode)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	if (test_opt2(inode->i_sb, DAX_NEVER))
		return false;
	if (!S_ISREG(inode->i_mode))
		return false;
	if (ext4_should_journal_data(inode))
		return false;
	if (ext4_has_inline_data(inode))
		return false;
	if (ext4_test_inode_flag(inode, EXT4_INODE_ENCRYPT))
		return false;
	if (ext4_test_inode_flag(inode, EXT4_INODE_VERITY))
		return false;
	if (!test_bit(EXT4_FLAGS_BDEV_IS_DAX, &sbi->s_ext4_flags))
		return false;
	if (test_opt(inode->i_sb, DAX_ALWAYS))
		return true;

	return ext4_test_inode_flag(inode, EXT4_INODE_DAX);
}