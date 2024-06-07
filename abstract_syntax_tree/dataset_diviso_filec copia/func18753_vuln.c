static int fill_autodev(const struct lxc_rootfs *rootfs)
{
	int ret;
	char path[MAXPATHLEN];
	int i;
	mode_t cmask;

	INFO("STR");

	ret = snprintf(path, MAXPATHLEN, "STR");
	if (ret < 0 || ret >= MAXPATHLEN) {
		ERROR("STR");
		return -1;
	}

	if (!dir_exists(path))  
		return 0;

	INFO("STR");
	cmask = umask(S_IXUSR | S_IXGRP | S_IXOTH);
	for (i = 0; i < sizeof(lxc_devs) / sizeof(lxc_devs[0]); i++) {
		const struct lxc_devs *d = &lxc_devs[i];
		ret = snprintf(path, MAXPATHLEN, "STR", d->name);
		if (ret < 0 || ret >= MAXPATHLEN)
			return -1;
		ret = mknod(path, d->mode, makedev(d->maj, d->min));
		if (ret && errno != EEXIST) {
			char hostpath[MAXPATHLEN];
			FILE *pathfile;

			
			
			ret = snprintf(hostpath, MAXPATHLEN, "STR", d->name);
			if (ret < 0 || ret >= MAXPATHLEN)
				return -1;
			pathfile = fopen(path, "STR");
			if (!pathfile) {
				SYSERROR("STR", path);
				return -1;
			}
			fclose(pathfile);
			if (mount(hostpath, path, 0, MS_BIND, NULL) != 0) {
				SYSERROR("STR",
					d->name);
				return -1;
			}
		}
	}
	umask(cmask);

	INFO("STR");
	return 0;
}