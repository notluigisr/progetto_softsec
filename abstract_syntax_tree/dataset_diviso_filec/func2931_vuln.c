int fpm_scoreboard_init_main() 
{
	struct fpm_worker_pool_s *wp;
	unsigned int i;

#ifdef HAVE_TIMES
#if (defined(HAVE_SYSCONF) && defined(_SC_CLK_TCK))
	fpm_scoreboard_tick = sysconf(_SC_CLK_TCK);
#else 
#ifdef HZ
	fpm_scoreboard_tick = HZ;
#else 
	fpm_scoreboard_tick = 100;
#endif 
#endif 
	zlog(ZLOG_DEBUG, "STR", fpm_scoreboard_tick);
#endif 


	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		size_t scoreboard_size, scoreboard_nprocs_size;
		void *shm_mem;

		if (wp->config->pm_max_children < 1) {
			zlog(ZLOG_ERROR, "STR", wp->config->name);
			return -1;
		}

		if (wp->scoreboard) {
			zlog(ZLOG_ERROR, "STR", wp->config->name);
			return -1;
		}

		scoreboard_size        = sizeof(struct fpm_scoreboard_s) + (wp->config->pm_max_children) * sizeof(struct fpm_scoreboard_proc_s *);
		scoreboard_nprocs_size = sizeof(struct fpm_scoreboard_proc_s) * wp->config->pm_max_children;
		shm_mem                = fpm_shm_alloc(scoreboard_size + scoreboard_nprocs_size);

		if (!shm_mem) {
			return -1;
		}
		wp->scoreboard         = shm_mem;
		wp->scoreboard->nprocs = wp->config->pm_max_children;
		shm_mem               += scoreboard_size;

		for (i = 0; i < wp->scoreboard->nprocs; i++, shm_mem += sizeof(struct fpm_scoreboard_proc_s)) {
			wp->scoreboard->procs[i] = shm_mem;
		}

		wp->scoreboard->pm          = wp->config->pm;
		wp->scoreboard->start_epoch = time(NULL);
		strlcpy(wp->scoreboard->pool, wp->config->name, sizeof(wp->scoreboard->pool));

		if (wp->shared) {
			
			wp->scoreboard->shared = wp->shared->scoreboard;
		}
	}
	return 0;
}