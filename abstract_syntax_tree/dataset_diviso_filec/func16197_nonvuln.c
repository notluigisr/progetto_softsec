void fpm_request_finished() 
{
	struct fpm_scoreboard_proc_s *proc;
	struct timeval now;

	fpm_clock_get(&now);

	proc = fpm_scoreboard_proc_acquire(NULL, -1, 0);
	if (proc == NULL) {
		zlog(ZLOG_WARNING, "STR");
		return;
	}

	proc->request_stage = FPM_REQUEST_FINISHED;
	proc->tv = now;
	fpm_scoreboard_proc_release(proc);
}