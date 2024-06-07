static void smack_inode_free_security(struct inode *inode)
{
	kfree(inode->i_security);
	inode->i_security = NULL;
}