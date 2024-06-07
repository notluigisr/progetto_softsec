static int mount_entry_on_relative_rootfs(struct mntent *mntent,
					  const char *rootfs)
{
	char path[MAXPATHLEN];
	int ret;

	
	ret = snprintf(path, sizeof(path), "STR", rootfs, mntent->mnt_dir);
	if (ret >= sizeof(path)) {
		ERROR("STR");
		return -1;
	}

	return mount_entry_on_generic(mntent, path);
}