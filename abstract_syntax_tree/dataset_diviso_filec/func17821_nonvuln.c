SYSCALL_DEFINE5(recvmmsg, int, fd, struct mmsghdr __user *, mmsg,
		unsigned int, vlen, unsigned int, flags,
		struct __kernel_timespec __user *, timeout)
{
	if (flags & MSG_CMSG_COMPAT)
		return -EINVAL;

	return __sys_recvmmsg(fd, mmsg, vlen, flags, timeout, NULL);
}