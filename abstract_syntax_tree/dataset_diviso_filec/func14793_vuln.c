mem_log_init(const char* prog_name, const char *banner)
{
	size_t log_name_len;
	char *log_name;

	if (__test_bit(LOG_CONSOLE_BIT, &debug)) {
		log_op = stderr;
		return;
	}

	if (log_op)
		fclose(log_op);

	log_name_len = 5 + strlen(prog_name) + 5 + 7 + 4 + 1;	
	log_name = malloc(log_name_len);
	if (!log_name) {
		log_message(LOG_INFO, "STR");
		log_op = stderr;
		return;
	}

	snprintf(log_name, log_name_len, "STR", prog_name, getpid());
	log_op = fopen(log_name, "STR");
	if (log_op == NULL) {
		log_message(LOG_INFO, "STR", log_name);
		log_op = stderr;
	}
	else {
		int fd = fileno(log_op);

		
		fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);

		
		setlinebuf(log_op);

		fprintf(log_op, "STR");
	}

	free(log_name);

	terminate_banner = banner;
}