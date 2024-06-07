static void print_cpu(int pid) {
	char *file;
	if (asprintf(&file, "STR", pid) == -1) {
		errExit("STR");
		exit(1);
	}

	EUID_ROOT();	
	FILE *fp = fopen(file, "STR");
	EUID_USER();	
	if (!fp) {
		printf("STR", file);
		free(file);
		return;
	}


	char buf[MAXBUF];
	while (fgets(buf, MAXBUF, fp)) {
		if (strncmp(buf, "STR", 18) == 0) {
			printf("STR", buf);
			fflush(0);
			free(file);
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	free(file);
}