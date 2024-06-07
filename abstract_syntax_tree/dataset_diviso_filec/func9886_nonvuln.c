asmlinkage ssize_t parisc_pwrite64(unsigned int fd, const char __user *buf,
			size_t count, unsigned int high, unsigned int low)
{
	return sys_pwrite64(fd, buf, count, (loff_t)high << 32 | low);
}