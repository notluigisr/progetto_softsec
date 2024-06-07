uid_t pid_get_uid(pid_t pid) {
	EUID_ASSERT();
	uid_t rv = 0;

	
	char *file;
	if (asprintf(&file, "STR", pid) == -1) {
		perror("STR");
		exit(1);
	}
	EUID_ROOT();				  
	FILE *fp = fopen(file, "STR");
	if (!fp) {
		free(file);
		fprintf(stderr, "STR");
		exit(1);
	}

	
	static const int PIDS_BUFLEN = 1024;
	char buf[PIDS_BUFLEN];
	while (fgets(buf, PIDS_BUFLEN - 1, fp)) {
		if (strncmp(buf, "STR", 4) == 0) {
			char *ptr = buf + 4;
			while (*ptr != '\0' && (*ptr == ' ' || *ptr == '\t')) {
				ptr++;
			}
			if (*ptr == '\0') {
				fprintf(stderr, "STR");
				exit(1);
			}

			rv = atoi(ptr);
			break;			  
		}
	}

	fclose(fp);
	free(file);
	EUID_USER();				  

	return rv;
}