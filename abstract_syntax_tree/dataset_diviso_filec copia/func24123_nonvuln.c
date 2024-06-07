int security_inode_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	if (unlikely(IS_PRIVATE(dir)))
		return 0;
	return security_ops->inode_mkdir(dir, dentry, mode);
}