static struct file *__fget_files(struct files_struct *files, unsigned int fd,
				 fmode_t mask, unsigned int refs)
{
	struct file *file;

	rcu_read_lock();
loop:
	file = files_lookup_fd_rcu(files, fd);
	if (file) {
		
		if (file->f_mode & mask)
			file = NULL;
		else if (!get_file_rcu_many(file, refs))
			goto loop;
	}
	rcu_read_unlock();

	return file;
}