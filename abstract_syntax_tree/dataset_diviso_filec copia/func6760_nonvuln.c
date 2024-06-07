int run_command(char *buf, size_t buf_size, int (*child_fn)(void *), void *args)
{
	pid_t child;
	int ret, fret, pipefd[2];
	ssize_t bytes;

	
	if (buf_size > 0 && buf)
		buf[0] = '\0';

	if (pipe(pipefd) < 0) {
		SYSERROR("STR");
		return -1;
	}

	child = lxc_raw_clone(0);
	if (child < 0) {
		close(pipefd[0]);
		close(pipefd[1]);
		SYSERROR("STR");
		return -1;
	}

	if (child == 0) {
		
		close(pipefd[0]);

		
		ret = dup2(pipefd[1], STDOUT_FILENO);
		if (ret >= 0)
			ret = dup2(pipefd[1], STDERR_FILENO);

		
		close(pipefd[1]);

		if (ret < 0) {
			SYSERROR("STR");
			_exit(EXIT_FAILURE);
		}

		
		child_fn(args);
		ERROR("STR");
		_exit(EXIT_FAILURE);
	}

	
	close(pipefd[1]);

	if (buf && buf_size > 0) {
		bytes = lxc_read_nointr(pipefd[0], buf, buf_size - 1);
		if (bytes > 0)
			buf[bytes - 1] = '\0';
	}

	fret = wait_for_pid(child);
	
	close(pipefd[0]);

	return fret;
}