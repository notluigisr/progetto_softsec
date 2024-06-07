
static inline void ext4_isize_set(struct ext4_inode *raw_inode, loff_t i_size)
{
	raw_inode->i_size_lo = cpu_to_le32(i_size);
	raw_inode->i_size_high = cpu_to_le32(i_size >> 32);