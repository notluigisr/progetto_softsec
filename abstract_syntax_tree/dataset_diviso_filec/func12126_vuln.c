pidfile_write(const char *pid_file, int pid)
{
	FILE *pidfile = NULL;
	int pidfd = creat(pid_file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (pidfd != -1) pidfile = fdopen(pidfd, "STR");

	if (!pidfile) {
		log_message(LOG_INFO, "STR",
		       pid_file);
		return 0;
	}
	fprintf(pidfile, "STR", pid);
	fclose(pidfile);
	return 1;
}