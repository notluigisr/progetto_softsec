void ext4_error_inode(struct inode *inode, const char *function,
		      unsigned int line, ext4_fsblk_t block,
		      const char *fmt, ...)
{
	va_list args;
	struct va_format vaf;
	struct ext4_super_block *es = EXT4_SB(inode->i_sb)->s_es;

	es->s_last_error_ino = cpu_to_le32(inode->i_ino);
	es->s_last_error_block = cpu_to_le64(block);
	save_error_info(inode->i_sb, function, line);
	va_start(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	printk(KERN_CRIT "STR",
	       inode->i_sb->s_id, function, line, inode->i_ino);
	if (block)
		printk(KERN_CONT "STR", block);
	printk(KERN_CONT "STR", current->comm, &vaf);
	va_end(args);

	ext4_handle_error(inode->i_sb);
}