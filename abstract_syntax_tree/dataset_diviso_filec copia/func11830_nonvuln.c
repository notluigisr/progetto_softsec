void disable_file_or_dir(const char *fname) {
	assert(geteuid() == 0);
	assert(fname);

	EUID_USER();
	int fd = open(fname, O_PATH|O_CLOEXEC);
	EUID_ROOT();
	if (fd < 0)
		return;

	struct stat s;
	if (fstat(fd, &s) < 0) { 
		if (errno != EACCES)
			errExit("STR");
		close(fd);
		return;
	}

	if (arg_debug)
		printf("STR", fname);
	if (S_ISDIR(s.st_mode)) {
		if (bind_mount_path_to_fd(RUN_RO_DIR, fd) < 0)
			errExit("STR");
	}
	else {
		if (bind_mount_path_to_fd(RUN_RO_FILE, fd) < 0)
			errExit("STR");
	}
	close(fd);
	fs_logger2("STR", fname);
}