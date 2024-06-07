int mount_proc_if_needed(const char *rootfs)
{
	char path[MAXPATHLEN];
	char link[20];
	int linklen, ret;
	int mypid;

	ret = snprintf(path, MAXPATHLEN, "STR", rootfs);
	if (ret < 0 || ret >= MAXPATHLEN) {
		SYSERROR("STR");
		return -1;
	}
	memset(link, 0, 20);
	linklen = readlink(path, link, 20);
	mypid = (int)getpid();
	INFO("STR", mypid, link);
	ret = snprintf(path, MAXPATHLEN, "STR", rootfs);
	if (ret < 0 || ret >= MAXPATHLEN) {
		SYSERROR("STR");
		return -1;
	}
	if (linklen < 0) 
		goto domount;
	if (atoi(link) != mypid) {
		
		umount2(path, MNT_DETACH); 
		goto domount;
	}
	
	return 0;

domount:
	if (mount("STR", 0, NULL))
		return -1;
	INFO("STR");
	return 1;
}