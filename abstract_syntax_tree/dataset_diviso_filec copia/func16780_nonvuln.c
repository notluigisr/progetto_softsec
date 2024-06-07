int security_path_truncate(struct path *path, loff_t length,
			   unsigned int time_attrs)
{
	if (unlikely(IS_PRIVATE(path->dentry->d_inode)))
		return 0;
	return security_ops->path_truncate(path, length, time_attrs);
}