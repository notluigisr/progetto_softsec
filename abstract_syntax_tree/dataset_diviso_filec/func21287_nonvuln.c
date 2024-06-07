static int proc_task_instantiate(struct inode *dir,
	struct dentry *dentry, struct task_struct *task, const void *ptr)
{
	struct inode *inode;
	inode = proc_pid_make_inode(dir->i_sb, task, S_IFDIR | S_IRUGO | S_IXUGO);

	if (!inode)
		goto out;
	inode->i_op = &proc_tid_base_inode_operations;
	inode->i_fop = &proc_tid_base_operations;
	inode->i_flags|=S_IMMUTABLE;

	set_nlink(inode, nlink_tid);

	d_set_d_op(dentry, &pid_dentry_operations);

	d_add(dentry, inode);
	
	if (pid_revalidate(dentry, 0))
		return 0;
out:
	return -ENOENT;
}