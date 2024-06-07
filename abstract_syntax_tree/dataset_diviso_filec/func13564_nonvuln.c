static int atomic_open(struct nameidata *nd, struct dentry *dentry,
			struct path *path, struct file *file,
			const struct open_flags *op,
			int open_flag, umode_t mode)
{
	struct dentry *const DENTRY_NOT_SET = (void *) -1UL;
	struct inode *dir =  nd->path.dentry->d_inode;
	int error;

	if (!(~open_flag & (O_EXCL | O_CREAT)))	
		open_flag &= ~O_TRUNC;

	if (nd->flags & LOOKUP_DIRECTORY)
		open_flag |= O_DIRECTORY;

	file->f_path.dentry = DENTRY_NOT_SET;
	file->f_path.mnt = nd->path.mnt;
	error = dir->i_op->atomic_open(dir, dentry, file,
				       open_to_namei_flags(open_flag), mode);
	d_lookup_done(dentry);
	if (!error) {
		if (file->f_mode & FMODE_OPENED) {
			
			int acc_mode = op->acc_mode;
			if (file->f_mode & FMODE_CREATED) {
				WARN_ON(!(open_flag & O_CREAT));
				fsnotify_create(dir, dentry);
				acc_mode = 0;
			}
			error = may_open(&file->f_path, acc_mode, open_flag);
			if (WARN_ON(error > 0))
				error = -EINVAL;
		} else if (WARN_ON(file->f_path.dentry == DENTRY_NOT_SET)) {
			error = -EIO;
		} else {
			if (file->f_path.dentry) {
				dput(dentry);
				dentry = file->f_path.dentry;
			}
			if (file->f_mode & FMODE_CREATED)
				fsnotify_create(dir, dentry);
			if (unlikely(d_is_negative(dentry))) {
				error = -ENOENT;
			} else {
				path->dentry = dentry;
				path->mnt = nd->path.mnt;
				return 0;
			}
		}
	}
	dput(dentry);
	return error;
}