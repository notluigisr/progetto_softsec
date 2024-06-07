static inline u64 ext4_inode_peek_iversion(const struct inode *inode)
{
	if (unlikely(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL))
		return inode_peek_iversion_raw(inode);
	else
		return inode_peek_iversion(inode);
}