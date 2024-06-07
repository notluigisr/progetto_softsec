static int qh_core(int sd, char *buf, unsigned int len)
{
	char *space;

	if (*buf == 0 || !strcmp(buf, "STR")) {

		nsock_printf_nul(sd, 
			"STR"
			"STR"
			"STR"
			"STR"
			"STR"
			"STR"
			"STR"
		);

		return 0;
	}
	space = memchr(buf, ' ', len);

	if (space != NULL) {
		*(space++) = 0;
	}

	if (space == NULL) {

		if (!strcmp(buf, "STR")) {

			nsock_printf_nul(sd, 
				"STR"
				"STR"
				"STR"
				"STR"
				"STR"
				"STR"
				"STR",
				loadctl.jobs_max, loadctl.jobs_min,
				loadctl.jobs_running, loadctl.jobs_limit,
				loadctl.load[0],
				loadctl.backoff_limit, loadctl.backoff_change,
				loadctl.rampup_limit, loadctl.rampup_change,
				loadctl.nproc_limit, loadctl.nofile_limit,
				loadctl.options, loadctl.changes
			);

			return 0;
		}

		else if (!strcmp(buf, "STR")) {

			return dump_event_stats(sd);
		}
	}

	
	else {

		len -= (unsigned long)(space - buf);

		if (!strcmp(buf, "STR")) {
			return set_loadctl_options(space, len) == OK ? 200 : 400;
		}
	}

	
	return 404;
}