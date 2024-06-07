void touch_file_as_user(const char *fname, mode_t mode) {
	pid_t child = fork();
	if (child < 0)
		errExit("STR");
	if (child == 0) {
		
		drop_privs(0);

		int fd = open(fname, O_RDONLY|O_CREAT|O_EXCL|O_CLOEXEC, S_IRUSR | S_IWUSR);
		if (fd > -1) {
			int err = fchmod(fd, mode);
			(void) err;
			close(fd);
		}
		else
			fwarning("STR", fname);

		__gcov_flush();

		_exit(0);
	}
	
	waitpid(child, NULL, 0);
}