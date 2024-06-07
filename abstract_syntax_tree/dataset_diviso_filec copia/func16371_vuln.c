static uint64_t extract_caps(int pid) {
	EUID_ASSERT();

	char *file;
	if (asprintf(&file, "STR", pid) == -1)
		errExit("STR");

	EUID_ROOT();	
	FILE *fp = fopen(file, "STR");
	EUID_USER();	
	if (!fp)
		goto errexit;

	char buf[MAXBUF];
	while (fgets(buf, MAXBUF, fp)) {
		if (strncmp(buf, "STR", 8) == 0) {
			char *ptr = buf + 8;
			unsigned long long val;
			sscanf(ptr, "STR", &val);
			free(file);
			fclose(fp);
			return val;
		}
	}
	fclose(fp);

errexit:
	free(file);
	fprintf(stderr, "STR");
	exit(1);
}