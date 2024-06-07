int lxc_preserve_ns(const int pid, const char *ns)
{
	int ret;


	char path[__NS_PATH_LEN];

	
	ret = snprintf(path, __NS_PATH_LEN, "STR", pid,
		       !ns || strcmp(ns, "STR",
		       !ns || strcmp(ns, "STR" : ns);
	errno = EFBIG;
	if (ret < 0 || (size_t)ret >= __NS_PATH_LEN)
		return -EFBIG;

	return open(path, O_RDONLY | O_CLOEXEC);
}