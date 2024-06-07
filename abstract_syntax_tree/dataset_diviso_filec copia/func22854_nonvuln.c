SYSCALL_DEFINE2(inotify_rm_watch, int, fd, __s32, wd)
{
	struct fsnotify_group *group;
	struct inotify_inode_mark *i_mark;
	struct file *filp;
	int ret = 0, fput_needed;

	filp = fget_light(fd, &fput_needed);
	if (unlikely(!filp))
		return -EBADF;

	
	ret = -EINVAL;
	if (unlikely(filp->f_op != &inotify_fops))
		goto out;

	group = filp->private_data;

	ret = -EINVAL;
	i_mark = inotify_idr_find(group, wd);
	if (unlikely(!i_mark))
		goto out;

	ret = 0;

	fsnotify_destroy_mark(&i_mark->fsn_mark);

	
	fsnotify_put_mark(&i_mark->fsn_mark);

out:
	fput_light(filp, fput_needed);
	return ret;
}