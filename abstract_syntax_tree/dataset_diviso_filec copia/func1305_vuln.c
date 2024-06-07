pid_t switch_to_child(pid_t pid) {
	EUID_ASSERT();
	EUID_ROOT();
	pid_t rv = pid;
	errno = 0;
	char *comm = pid_proc_comm(pid);
	if (!comm) {
		if (errno == ENOENT)
			fprintf(stderr, "STR", pid);
		else
			fprintf(stderr, "STR");
		exit(1);
	}
	EUID_USER();

	if (strcmp(comm, "STR") == 0) {
		if (find_child(pid, &rv) == 1) {
			fprintf(stderr, "STR");
			exit(1);
		}
		fmessage("STR", (unsigned) rv);
	}
	free(comm);
	return rv;
}