static int cdrom_do_generic_command(unsigned int fd, unsigned int cmd, unsigned long arg)
{
	struct cdrom_generic_command __user *cgc;
	struct cdrom_generic_command32 __user *cgc32;
	u32 data;
	unsigned char dir;
	int itmp;

	cgc = compat_alloc_user_space(sizeof(*cgc));
	cgc32 = compat_ptr(arg);

	if (copy_in_user(&cgc->cmd, &cgc32->cmd, sizeof(cgc->cmd)) ||
	    get_user(data, &cgc32->buffer) ||
	    put_user(compat_ptr(data), &cgc->buffer) ||
	    copy_in_user(&cgc->buflen, &cgc32->buflen,
			 (sizeof(unsigned int) + sizeof(int))) ||
	    get_user(data, &cgc32->sense) ||
	    put_user(compat_ptr(data), &cgc->sense) ||
	    get_user(dir, &cgc32->data_direction) ||
	    put_user(dir, &cgc->data_direction) ||
	    get_user(itmp, &cgc32->quiet) ||
	    put_user(itmp, &cgc->quiet) ||
	    get_user(itmp, &cgc32->timeout) ||
	    put_user(itmp, &cgc->timeout) ||
	    get_user(data, &cgc32->reserved[0]) ||
	    put_user(compat_ptr(data), &cgc->reserved[0]))
		return -EFAULT;

	return sys_ioctl(fd, cmd, (unsigned long) cgc);
}