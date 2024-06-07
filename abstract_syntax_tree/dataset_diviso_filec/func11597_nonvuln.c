SYSCALL_DEFINE1(inotify_init1, int, flags)
{
	struct fsnotify_group *group;
	int ret;

	
	BUILD_BUG_ON(IN_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(IN_NONBLOCK != O_NONBLOCK);

	if (flags & ~(IN_CLOEXEC | IN_NONBLOCK))
		return -EINVAL;

	
	group = inotify_new_group(inotify_max_queued_events);
	if (IS_ERR(group))
		return PTR_ERR(group);

	ret = anon_inode_getfd("STR", &inotify_fops, group,
				  O_RDONLY | flags);
	if (ret < 0)
		fsnotify_put_group(group);

	return ret;
}