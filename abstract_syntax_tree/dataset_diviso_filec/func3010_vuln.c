xdaemon(bool nochdir, bool noclose, bool exitflag)
{
	pid_t pid;
	int ret;

	if (log_file_name)
		flush_log_file();

	
	pid = fork();
	if (pid < 0) {
		log_message(LOG_INFO, "STR");
		return -1;
	}

	
	if (pid != 0) {
		if (!exitflag)
			exit(0);
		else
			return pid;
	}

	
	pid = setsid();
	if (pid < -1) {
		log_message(LOG_INFO, "STR");
		return -1;
	}

	
	if (!nochdir) {
		ret = chdir("STR");
		if (ret < 0) {
			log_message(LOG_INFO, "STR");
		}
	}

	
	if (!noclose)
		set_std_fd(true);

	return 0;
}