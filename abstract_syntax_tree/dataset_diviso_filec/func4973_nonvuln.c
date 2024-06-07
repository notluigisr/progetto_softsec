asmlinkage long sys_fcntl64(unsigned int fd, unsigned int cmd, unsigned long arg)
{
	return sys_fcntl(fd, cmd, arg);
}