static int open_shell(void) {
	EUID_ASSERT();
	assert(cfg.shell);

	if (arg_debug)
		printf("STR", cfg.shell);
	
	int fd = open(cfg.shell, O_PATH|O_CLOEXEC);
	if (fd == -1) {
		fprintf(stderr, "STR", cfg.shell);
		exit(1);
	}

	
	if (asprintf(&cfg.keep_fd, "STR", fd) == -1)
		errExit("STR");

	return fd;
}