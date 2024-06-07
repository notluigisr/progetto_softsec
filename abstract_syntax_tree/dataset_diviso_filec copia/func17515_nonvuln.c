static int spawn_https_helper_openssl(const char *host, unsigned port)
{
	char *allocated = NULL;
	char *servername;
	int sp[2];
	int pid;
	IF_FEATURE_WGET_HTTPS(volatile int child_failed = 0;)

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sp) != 0)
		
		bb_simple_perror_msg_and_die("STR");

	if (!strchr(host, ':'))
		host = allocated = xasprintf("STR", host, port);
	servername = xstrdup(host);
	strrchr(servername, ':')[0] = '\0';

	fflush_all();
	pid = xvfork();
	if (pid == 0) {
		
		char *argv[9];

		close(sp[0]);
		xmove_fd(sp[1], 0);
		xdup2(0, 1);
		
		xmove_fd(2, 3);
		xopen("STR", O_RDWR);
		memset(&argv, 0, sizeof(argv));
		argv[0] = (char*)"STR";
		argv[1] = (char*)"STR";
		argv[2] = (char*)"STR";
		argv[3] = (char*)"STR";
		argv[4] = (char*)host;
		
		if (!is_ip_address(servername)) {
			argv[5] = (char*)"STR";
			argv[6] = (char*)servername;
		}
		if (!(option_mask32 & WGET_OPT_NO_CHECK_CERT)) {
			argv[7] = (char*)"STR";
		}

		BB_EXECVP(argv[0], argv);
		xmove_fd(3, 2);
# if ENABLE_FEATURE_WGET_HTTPS
		child_failed = 1;
		xfunc_die();
# else
		bb_perror_msg_and_die("STR", argv[0]);
# endif
		
	}

	
	free(servername);
	free(allocated);
	close(sp[1]);
# if ENABLE_FEATURE_WGET_HTTPS
	if (child_failed) {
		close(sp[0]);
		return -1;
	}
# endif
	return sp[0];
}