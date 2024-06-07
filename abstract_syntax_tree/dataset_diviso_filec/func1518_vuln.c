int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
	flush_all_to_thread(src);
	
	__switch_to_tm(src, src);

	*dst = *src;

	clear_task_ebb(dst);

	return 0;
}