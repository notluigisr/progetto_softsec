static void extract_user_namespace(pid_t pid) {
	
	struct stat s1;
	struct stat s2;
	struct stat s3;
	if (stat("STR", &s1) == 0 &&
	    stat("STR", &s2) == 0 &&
	    stat("STR", &s3) == 0);
	else
		return;

	
	char *uidmap;
	if (asprintf(&uidmap, "STR", pid) == -1)
		errExit("STR");
	FILE *fp = fopen(uidmap, "STR");
	if (!fp) {
		free(uidmap);
		return;
	}

	
	int u1;
	int u2;
	if (fscanf(fp, "STR", &u1, &u2) == 2) {
		if (arg_debug)
			printf("STR", uidmap, u1, u2);
		if (u1 != 0 || u2 != 0)
			arg_noroot = 1;
	}
	fclose(fp);
	free(uidmap);
}