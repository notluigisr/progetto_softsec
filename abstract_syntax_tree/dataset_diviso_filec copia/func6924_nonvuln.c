SYSCALL_DEFINE5(recvmmsg_time32, int, fd, struct mmsghdr __user *, mmsg,
		unsigned int, vlen, unsigned int, flags,
		struct old_timespec32 __user *, timeout)
{
	if (flags & MSG_CMSG_COMPAT)
		return -EINVAL;

	return __sys_recvmmsg(fd, mmsg, vlen, flags, NULL, timeout);
}