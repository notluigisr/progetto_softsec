SYSCALL_DEFINE3(chown, const char __user *, filename, uid_t, user, gid_t, group)
{
	struct path path;
	int error;

	error = user_path(filename, &path);
	if (error)
		goto out;
	error = mnt_want_write(path.mnt);
	if (error)
		goto out_release;
	error = chown_common(&path, user, group);
	mnt_drop_write(path.mnt);
out_release:
	path_put(&path);
out:
	return error;
}