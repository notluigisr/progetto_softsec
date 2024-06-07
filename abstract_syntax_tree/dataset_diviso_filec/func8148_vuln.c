SYSCALL_DEFINE1(epoll_create1, int, flags)
{
	int error;
	struct eventpoll *ep = NULL;

	
	BUILD_BUG_ON(EPOLL_CLOEXEC != O_CLOEXEC);

	if (flags & ~EPOLL_CLOEXEC)
		return -EINVAL;
	
	error = ep_alloc(&ep);
	if (error < 0)
		return error;
	
	error = anon_inode_getfd("STR", &eventpoll_fops, ep,
				 O_RDWR | (flags & O_CLOEXEC));
	if (error < 0)
		ep_free(ep);

	return error;
}