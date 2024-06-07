static int vfat_revalidate(struct dentry *dentry, struct nameidata *nd)
{
	if (nd && nd->flags & LOOKUP_RCU)
		return -ECHILD;

	
	if (dentry->d_inode)
		return 1;
	return vfat_revalidate_shortname(dentry);
}