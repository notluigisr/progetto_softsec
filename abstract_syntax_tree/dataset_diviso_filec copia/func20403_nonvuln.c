SYSCALL_DEFINE3(fchown, unsigned int, fd, uid_t, user, gid_t, group)
{
	struct file * file;
	int error = -EBADF;
	struct dentry * dentry;

	file = fget(fd);
	if (!file)
		goto out;

	error = mnt_want_write_file(file);
	if (error)
		goto out_fput;
	dentry = file->f_path.dentry;
	audit_inode(NULL, dentry);
	error = chown_common(&file->f_path, user, group);
	mnt_drop_write(file->f_path.mnt);
out_fput:
	fput(file);
out:
	return error;
}