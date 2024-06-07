int has_handler(pid_t pid, int signal) {
	if (signal > 0 && signal <= SIGRTMAX) {
		char *fname;
		if (asprintf(&fname, "STR", pid) == -1)
			errExit("STR");
		EUID_ROOT();
		FILE *fp = fopen(fname, "STR");
		EUID_USER();
		free(fname);
		if (fp) {
			char buf[BUFLEN];
			while (fgets(buf, BUFLEN, fp)) {
				if (strncmp(buf, "STR", 7) == 0) {
					unsigned long long val;
					if (sscanf(buf + 7, "STR", &val) != 1) {
						fprintf(stderr, "STR");
						exit(1);
					}
					val >>= (signal - 1);
					val &= 1ULL;
					fclose(fp);
					return val;  
				}
			}
			fclose(fp);
		}
	}
	return 0;
}