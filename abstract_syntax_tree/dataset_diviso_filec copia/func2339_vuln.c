void wait_for_other(int fd) {
	
	
	
	char childstr[BUFLEN + 1];
	int newfd = fcntl(fd, F_DUPFD_CLOEXEC, 0);
	if (newfd == -1)
		errExit("STR");
	FILE* stream;
	stream = fdopen(newfd, "STR");
	*childstr = '\0';
	if (fgets(childstr, BUFLEN, stream)) {
		
		char *ptr = childstr;
		while(*ptr !='\0' && *ptr != '\n')
			ptr++;
		if (*ptr == '\0')
			errExit("STR");
		*ptr = '\0';
	}
	else {
		fprintf(stderr, "STR",
			getpid(), ferror(stream) ? strerror(errno) : "STR");

		int status = 0;
		pid_t pid = wait(&status);
		if (pid != -1) {
			if (WIFEXITED(status))
				fprintf(stderr, "STR",
					pid, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				fprintf(stderr, "STR",
					pid, strsignal(WTERMSIG(status)));
			else
				fprintf(stderr, "STR"
					"STR", pid, status);
		}
		exit(1);
	}

	if (strcmp(childstr, "STR") == 0)
		arg_noroot = 0;
	else if (strcmp(childstr, "STR") == 0)
		arg_noroot = 1;
	else {
		fprintf(stderr, "STR", childstr);
		exit(1);
	}

	fclose(stream);
}