static bool has_join_file(ProcessHandle sandbox) {
	
	int fd = process_rootfs_open(sandbox, RUN_JOIN_FILE);
	if (fd == -1)
		return false;
	struct stat s;
	if (fstat(fd, &s) == -1)
		errExit("STR");
	if (!S_ISREG(s.st_mode) || s.st_uid != 0 || s.st_size != 1) {
		close(fd);
		return false;
	}
	char status;
	if (read(fd, &status, 1) == 1 && status == SANDBOX_DONE) {
		close(fd);
		return true;
	}
	close(fd);
	return false;
}