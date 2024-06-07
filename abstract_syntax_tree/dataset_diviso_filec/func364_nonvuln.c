static int run_buffer(char *buffer)
{
	struct lxc_popen_FILE *f;
	char *output;
	int ret;

	f = lxc_popen(buffer);
	if (!f) {
		SYSERROR("STR");
		return -1;
	}

	output = malloc(LXC_LOG_BUFFER_SIZE);
	if (!output) {
		ERROR("STR");
		lxc_pclose(f);
		return -1;
	}

	while(fgets(output, LXC_LOG_BUFFER_SIZE, f->f))
		DEBUG("STR", output);

	free(output);

	ret = lxc_pclose(f);
	if (ret == -1) {
		SYSERROR("STR");
		return -1;
	} else if (WIFEXITED(ret) && WEXITSTATUS(ret) != 0) {
		ERROR("STR", WEXITSTATUS(ret));
		return -1;
	} else if (WIFSIGNALED(ret)) {
		ERROR("STR", WTERMSIG(ret),
		      strsignal(WTERMSIG(ret)));
		return -1;
	}

	return 0;
}