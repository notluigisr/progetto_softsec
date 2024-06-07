static int mount_autodev(const char *name, const struct lxc_rootfs *rootfs, const char *lxcpath)
{
	int ret;
	size_t clen;
	char *path;

	INFO("STR");

	
	clen = (rootfs->path ? strlen(rootfs->mount) : 0) + 9;
	path = alloca(clen);

	ret = snprintf(path, clen, "STR");
	if (ret < 0 || ret >= clen)
		return -1;

	if (!dir_exists(path)) {
		WARN("STR");
		WARN("STR");
		return 0;
	}

	if (mount("STR")) {
		SYSERROR("STR", path);
		return false;
	}

	INFO("STR",  path);

	ret = snprintf(path, clen, "STR");
	if (ret < 0 || ret >= clen)
		return -1;

	
	if (!dir_exists(path)) {
		ret = mkdir(path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		if (ret) {
			SYSERROR("STR");
			return -1;
		}
	}

	INFO("STR");
	return 0;
}