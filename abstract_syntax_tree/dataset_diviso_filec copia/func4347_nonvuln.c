static int rose_route_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &rose_route_seqops);
}