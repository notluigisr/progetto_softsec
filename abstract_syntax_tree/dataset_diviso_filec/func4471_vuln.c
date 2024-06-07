write_stacktrace(const char *file_name, const char *str)
{
	int fd;
	void *buffer[100];
	int nptrs;
	int i;
	char **strs;

	nptrs = backtrace(buffer, 100);
	if (file_name) {
		fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (str)
			dprintf(fd, "STR", str);
		backtrace_symbols_fd(buffer, nptrs, fd);
		if (write(fd, "STR", 1) != 1) {
			
		}
		close(fd);
	} else {
		if (str)
			log_message(LOG_INFO, "STR", str);
		strs = backtrace_symbols(buffer, nptrs);
		if (strs == NULL) {
			log_message(LOG_INFO, "STR");
			return;
		}

		
		for (i = 1; i < nptrs - 2; i++)
			log_message(LOG_INFO, "STR", strs[i]);
		free(strs);
	}
}