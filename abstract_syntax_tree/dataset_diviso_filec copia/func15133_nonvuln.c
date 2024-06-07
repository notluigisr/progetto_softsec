proc_file_write(struct file *file, const char __user *buffer,
		size_t count, loff_t *ppos)
{
	struct inode *inode = file->f_dentry->d_inode;
	struct proc_dir_entry * dp;
	
	dp = PDE(inode);

	if (!dp->write_proc)
		return -EIO;

	
	return dp->write_proc(file, buffer, count, dp->data);
}