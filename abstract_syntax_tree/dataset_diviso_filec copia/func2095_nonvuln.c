char *sched_trace_cfs_rq_path(struct cfs_rq *cfs_rq, char *str, int len)
{
	if (!cfs_rq) {
		if (str)
			strlcpy(str, "STR", len);
		else
			return NULL;
	}

	cfs_rq_tg_path(cfs_rq, str, len);
	return str;
}