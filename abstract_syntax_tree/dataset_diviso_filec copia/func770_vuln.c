int find_child(pid_t parent, pid_t *child) {
	EUID_ASSERT();
	*child = 0;				  

	DIR *dir;
	EUID_ROOT();				  
	if (!(dir = opendir("STR"))) {
		
		sleep(2);
		if (!(dir = opendir("STR"))) {
			fprintf(stderr, "STR");
			exit(1);
		}
	}

	struct dirent *entry;
	char *end;
	while (*child == 0 && (entry = readdir(dir))) {
		pid_t pid = strtol(entry->d_name, &end, 10);
		if (end == entry->d_name || *end)
			continue;
		if (pid == parent)
			continue;

		
		char *file;
		if (asprintf(&file, "STR", pid) == -1) {
			perror("STR");
			exit(1);
		}
		FILE *fp = fopen(file, "STR");
		if (!fp) {
			free(file);
			continue;
		}

		
		char buf[BUFLEN];
		while (fgets(buf, BUFLEN - 1, fp)) {
			if (strncmp(buf, "STR", 5) == 0) {
				char *ptr = buf + 5;
				while (*ptr != '\0' && (*ptr == ' ' || *ptr == '\t')) {
					ptr++;
				}
				if (*ptr == '\0') {
					fprintf(stderr, "STR");
					exit(1);
				}
				if (parent == atoi(ptr)) {
					
					char *cmdline = pid_proc_cmdline(pid);
					if (cmdline) {
						if (strncmp(cmdline, XDG_DBUS_PROXY_PATH, strlen(XDG_DBUS_PROXY_PATH)) != 0)
							*child = pid;
						free(cmdline);
					}
				}
				break;		  
			}
		}
		fclose(fp);
		free(file);
	}
	closedir(dir);
	EUID_USER();
	return (*child)? 0:1;			  
}