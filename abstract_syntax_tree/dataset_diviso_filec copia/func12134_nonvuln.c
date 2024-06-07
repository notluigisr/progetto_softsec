static int sg_proc_seq_show_int(struct seq_file *s, void *v)
{
	seq_printf(s, "STR", *((int *)s->private));
	return 0;
}