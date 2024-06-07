RETSIGTYPE remember_children(UNUSED(int val))
{
#ifdef WNOHANG
	int cnt, status;
	pid_t pid;
	
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		
		for (cnt = 0; cnt < MAXCHILDPROCS; cnt++) {
			if (pid_stat_table[cnt].pid == 0) {
				pid_stat_table[cnt].pid = pid;
				pid_stat_table[cnt].status = status;
				break;
			}
		}
	}
#endif
#ifndef HAVE_SIGACTION
	signal(SIGCHLD, remember_children);
#endif
}