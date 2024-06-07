static inline void io_uring_files_cancel(struct files_struct *files)
{
	if (current->io_uring && !xa_empty(&current->io_uring->xa))
		__io_uring_files_cancel(files);
}