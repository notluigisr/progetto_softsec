static bool io_file_supports_async(struct file *file)
{
	umode_t mode = file_inode(file)->i_mode;

	if (S_ISBLK(mode) || S_ISCHR(mode) || S_ISSOCK(mode))
		return true;
	if (S_ISREG(mode) && file->f_op != &io_uring_fops)
		return true;

	return false;
}