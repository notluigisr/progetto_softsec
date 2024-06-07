void dentry_update_name_case(struct dentry *dentry, const struct qstr *name)
{
	BUG_ON(!inode_is_locked(dentry->d_parent->d_inode));
	BUG_ON(dentry->d_name.len != name->len); 

	spin_lock(&dentry->d_lock);
	write_seqcount_begin(&dentry->d_seq);
	memcpy((unsigned char *)dentry->d_name.name, name->name, name->len);
	write_seqcount_end(&dentry->d_seq);
	spin_unlock(&dentry->d_lock);
}