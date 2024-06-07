int join_namespace(pid_t pid, char *type) {
	char *path;
	if (asprintf(&path, "STR", pid, type) == -1)
		errExit("STR");

	int fd = open(path, O_RDONLY);
	if (fd < 0)
		goto errout;

	if (syscall(__NR_setns, fd, 0) < 0) {
		close(fd);
		goto errout;
	}

	close(fd);
	free(path);
	return 0;

errout:
	free(path);
	fprintf(stderr, "STR", type);
	return -1;

}