int __ext4_mark_inode_dirty(handle_t *handle, struct inode *inode,
				const char *func, unsigned int line)
{
	struct ext4_iloc iloc;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	int err;

	might_sleep();
	trace_ext4_mark_inode_dirty(inode, _RET_IP_);
	err = ext4_reserve_inode_write(handle, inode, &iloc);
	if (err)
		goto out;

	if (EXT4_I(inode)->i_extra_isize < sbi->s_want_extra_isize)
		ext4_try_to_expand_extra_isize(inode, sbi->s_want_extra_isize,
					       iloc, handle);

	err = ext4_mark_iloc_dirty(handle, inode, &iloc);
out:
	if (unlikely(err))
		ext4_error_inode_err(inode, func, line, 0, err,
					"STR");
	return err;
}