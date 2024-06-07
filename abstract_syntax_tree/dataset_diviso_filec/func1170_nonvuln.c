static inline struct inode *isofs_iget(struct super_block *sb,
				       unsigned long block,
				       unsigned long offset)
{
	return __isofs_iget(sb, block, offset, 0);
}