static int cgroup_seqfile_show(struct seq_file *m, void *arg)
{
	struct cftype *cft = seq_cft(m);
	struct cgroup_subsys_state *css = seq_css(m);

	if (cft->seq_show)
		return cft->seq_show(m, arg);

	if (cft->read_u64)
		seq_printf(m, "STR", cft->read_u64(css, cft));
	else if (cft->read_s64)
		seq_printf(m, "STR", cft->read_s64(css, cft));
	else
		return -EINVAL;
	return 0;
}