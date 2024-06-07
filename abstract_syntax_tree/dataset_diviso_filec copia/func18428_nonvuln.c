nfs4_do_lookup_revalidate(struct inode *dir, struct dentry *dentry,
			  unsigned int flags)
{
	struct inode *inode;

	if (!(flags & LOOKUP_OPEN) || (flags & LOOKUP_DIRECTORY))
		goto full_reval;
	if (d_mountpoint(dentry))
		goto full_reval;

	inode = d_inode(dentry);

	
	if (inode == NULL)
		goto full_reval;

	if (nfs_verifier_is_delegated(dentry))
		return nfs_lookup_revalidate_delegated(dir, dentry, inode);

	
	if (!S_ISREG(inode->i_mode))
		goto full_reval;

	
	if (flags & (LOOKUP_EXCL | LOOKUP_REVAL))
		goto reval_dentry;

	
	if (!nfs_check_verifier(dir, dentry, flags & LOOKUP_RCU))
		goto reval_dentry;

	
	return 1;
reval_dentry:
	if (flags & LOOKUP_RCU)
		return -ECHILD;
	return nfs_lookup_revalidate_dentry(dir, dentry, inode);

full_reval:
	return nfs_do_lookup_revalidate(dir, dentry, flags);
}