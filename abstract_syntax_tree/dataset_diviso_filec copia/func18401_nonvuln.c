ep0_fasync (int f, struct file *fd, int on)
{
	struct dev_data		*dev = fd->private_data;
	
	VDEBUG (dev, "STR");
	return fasync_helper (f, fd, on, &dev->fasync);
}