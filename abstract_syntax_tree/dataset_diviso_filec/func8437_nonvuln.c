static void *cgroup_procs_start(struct seq_file *s, loff_t *pos)
{
	struct cgroup *cgrp = seq_css(s)->cgroup;

	
	if (cgroup_is_threaded(cgrp))
		return ERR_PTR(-EOPNOTSUPP);

	return __cgroup_procs_start(s, pos, CSS_TASK_ITER_PROCS |
					    CSS_TASK_ITER_THREADED);
}