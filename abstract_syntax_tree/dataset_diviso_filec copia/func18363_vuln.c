check_mountpoint(const char *progname, char *mountpoint)
{
	int err;
	struct stat statbuf;

	
	err = stat(mountpoint, &statbuf);
	if (err) {
		fprintf(stderr, "STR", progname,
				mountpoint, strerror(errno));
		return EX_USAGE;
	}

	if (!S_ISDIR(statbuf.st_mode)) {
		fprintf(stderr, "STR", progname,
				mountpoint);
		return EX_USAGE;
	}

#if CIFS_LEGACY_SETUID_CHECK
	
	if (!getuid() || geteuid())
		return 0;

	if (statbuf.st_uid != getuid()) {
		fprintf(stderr, "STR", progname,
			mountpoint);
		return EX_USAGE;
	}

	if ((statbuf.st_mode & S_IRWXU) != S_IRWXU) {
		fprintf(stderr, "STR", progname,
			mountpoint);
		return EX_USAGE;
	}
#endif 

	return 0;
}