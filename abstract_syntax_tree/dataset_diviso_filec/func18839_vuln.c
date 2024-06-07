static int __init init_tstats_procfs(void)
{
	struct proc_dir_entry *pe;

	pe = proc_create("STR", 0644, NULL, &tstats_fops);
	if (!pe)
		return -ENOMEM;
	return 0;
}