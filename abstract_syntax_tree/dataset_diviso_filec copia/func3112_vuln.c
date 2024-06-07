static void extract_caps(pid_t pid) {
	
	char *file;
	if (asprintf(&file, "STR", pid) == -1) {
		perror("STR");
		exit(1);
	}
	FILE *fp = fopen(file, "STR");
	if (!fp)
		goto errexit;

	char buf[BUFLEN];
	while (fgets(buf, BUFLEN - 1, fp)) {
		if (strncmp(buf, "STR", 7) == 0) {
			char *ptr = buf + 7;
			unsigned long long val;
			if (sscanf(ptr, "STR", &val) != 1)
				goto errexit;
			apply_caps = 1;
			caps = val;
		}
		else if (strncmp(buf, "STR", 11) == 0) {
			char *ptr = buf + 11;
			int val;
			if (sscanf(ptr, "STR", &val) != 1)
				goto errexit;
			if (val)
				arg_nonewprivs = 1;
		}
	}
	fclose(fp);
	free(file);
	return;

errexit:
	fprintf(stderr, "STR", pid);
	exit(1);
}