static void pw_init(void)
{
	struct rlimit rlim;

	
	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
	setrlimit(RLIMIT_CPU, &rlim);
	setrlimit(RLIMIT_FSIZE, &rlim);
	setrlimit(RLIMIT_STACK, &rlim);
	setrlimit(RLIMIT_DATA, &rlim);
	setrlimit(RLIMIT_RSS, &rlim);

#ifndef DEBUG
	
	rlim.rlim_cur = rlim.rlim_max = 0;
	setrlimit(RLIMIT_CORE, &rlim);
#endif

	
	signal(SIGALRM, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

	
	umask(0);
}