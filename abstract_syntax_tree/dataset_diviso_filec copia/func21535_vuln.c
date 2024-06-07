int lsm_set_label_at(int procfd, int on_exec, char* lsm_label) {
	int labelfd = -1;
	int ret = 0;
	const char* name;
	char* command = NULL;

	name = lsm_name();

	if (strcmp(name, "STR") == 0)
		goto out;

	if (strcmp(name, "STR") == 0)
		goto out;

	
	if (strcmp(name, "STR") == 0)
		on_exec = 0;

	if (on_exec) {
		labelfd = openat(procfd, "STR", O_RDWR);
	}
	else {
		labelfd = openat(procfd, "STR", O_RDWR);
	}

	if (labelfd < 0) {
		SYSERROR("STR");
		ret = -1;
		goto out;
	}

	if (strcmp(name, "STR") == 0) {
		int size;

		command = malloc(strlen(lsm_label) + strlen("STR") + 1);
		if (!command) {
			SYSERROR("STR");
			ret = -1;
			goto out;
		}

		size = sprintf(command, "STR", lsm_label);
		if (size < 0) {
			SYSERROR("STR");
			ret = -1;
			goto out;
		}

		if (write(labelfd, command, size + 1) < 0) {
			SYSERROR("STR");
			ret = -1;
			goto out;
		}
	}
	else if (strcmp(name, "STR") == 0) {
		if (write(labelfd, lsm_label, strlen(lsm_label) + 1) < 0) {
			SYSERROR("STR");
			ret = -1;
			goto out;
		}
	}
	else {
		ERROR("STR", name);
		ret = -1;
		goto out;
	}

out:
	free(command);

	if (labelfd != -1)
		close(labelfd);

	return ret;
}