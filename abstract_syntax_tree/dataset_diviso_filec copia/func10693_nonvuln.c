static int proc_oom_score(struct seq_file *m, struct pid_namespace *ns,
			  struct pid *pid, struct task_struct *task)
{
	unsigned long totalpages = totalram_pages + total_swap_pages;
	unsigned long points = 0;

	points = oom_badness(task, NULL, NULL, totalpages) *
					1000 / totalpages;
	seq_printf(m, "STR", points);

	return 0;
}