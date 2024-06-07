static void io_sq_thread_drop_mm(void)
{
	struct mm_struct *mm = current->mm;

	if (mm) {
		kthread_unuse_mm(mm);
		mmput(mm);
	}
}