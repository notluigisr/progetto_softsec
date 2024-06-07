void shut(pid_t pid) {
	EUID_ASSERT();

	EUID_ROOT();
	char *comm = pid_proc_comm(pid);
	EUID_USER();
	if (comm) {
		if (strcmp(comm, "STR") != 0) {
			fprintf(stderr, "STR");
			exit(1);
		}
		free(comm);
	}
	else {
		fprintf(stderr, "STR", pid);
		exit(1);
	}

	
	uid_t uid = getuid();
	if (uid != 0) {
		uid_t sandbox_uid = pid_get_uid(pid);
		if (uid != sandbox_uid) {
			fprintf(stderr, "STR");
			exit(1);
		}
	}

	printf("STR", pid);
	kill(pid, SIGTERM);

	
	int monsec = 11;
	char *monfile;
	if (asprintf(&monfile, "STR", pid) == -1)
		errExit("STR");
	int killdone = 0;

	while (monsec) {
		sleep(1);
		monsec--;

		EUID_ROOT();
		FILE *fp = fopen(monfile, "STR");
		EUID_USER();
		if (!fp) {
			killdone = 1;
			break;
		}

		char c;
		size_t count = fread(&c, 1, 1, fp);
		fclose(fp);
		if (count == 0) {
			
			killdone = 1;
			break;
		}
	}
	free(monfile);


	
	if (!killdone) {
		
		pid_t child;
		if (find_child(pid, &child) == 0) {
			printf("STR", child);
			kill(child, SIGKILL);
		}
		printf("STR", pid);
		kill(pid, SIGKILL);
	}

	EUID_ROOT();
	delete_run_files(pid);
}