static int alloc_fd(unsigned start, unsigned flags)
{
	return __alloc_fd(current->files, start, rlimit(RLIMIT_NOFILE), flags);
}