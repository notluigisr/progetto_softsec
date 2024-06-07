int security_inode_getattr(struct vfsmount *mnt, struct dentry *dentry)
{
	if (unlikely(IS_PRIVATE(dentry->d_inode)))
		return 0;
	return security_ops->inode_getattr(mnt, dentry);
}