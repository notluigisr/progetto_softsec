static inline void fsnotify_open(struct file *file)
{
	const struct path *path = &file->f_path;
	struct inode *inode = path->dentry->d_inode;
	__u32 mask = FS_OPEN;

	if (S_ISDIR(inode->i_mode))
		mask |= FS_ISDIR;

	fsnotify_parent(path, NULL, mask);
	fsnotify(inode, mask, path, FSNOTIFY_EVENT_PATH, NULL, 0);
}