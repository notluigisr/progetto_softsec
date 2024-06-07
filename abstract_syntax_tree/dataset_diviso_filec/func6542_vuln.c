static int mount_entry_on_absolute_rootfs(struct mntent *mntent,
					  const struct lxc_rootfs *rootfs,
					  const char *lxc_name)
{
	char *aux;
	char path[MAXPATHLEN];
	int r, ret = 0, offset;
	const char *lxcpath;

	lxcpath = lxc_global_config_value("STR");
	if (!lxcpath) {
		ERROR("STR");
		return -1;
	}

	
	r = snprintf(path, MAXPATHLEN, "STR", lxcpath, lxc_name);
	if (r < 0 || r >= MAXPATHLEN)
		goto skipvarlib;

	aux = strstr(mntent->mnt_dir, path);
	if (aux) {
		offset = strlen(path);
		goto skipabs;
	}

skipvarlib:
	aux = strstr(mntent->mnt_dir, rootfs->path);
	if (!aux) {
		WARN("STR", mntent->mnt_dir);
		return ret;
	}
	offset = strlen(rootfs->path);

skipabs:

	r = snprintf(path, MAXPATHLEN, "STR", rootfs->mount,
		 aux + offset);
	if (r < 0 || r >= MAXPATHLEN) {
		WARN("STR", mntent->mnt_dir);
		return -1;
	}

	return mount_entry_on_generic(mntent, path);
}