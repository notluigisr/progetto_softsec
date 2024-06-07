static int fuse_dev_fasync(int fd, struct file *file, int on)
{
	struct fuse_dev *fud = fuse_get_dev(file);

	if (!fud)
		return -EPERM;

	
	return fasync_helper(fd, file, on, &fud->fc->iq.fasync);
}