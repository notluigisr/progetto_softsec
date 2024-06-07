static int set_vesa_blanking(char __user *p)
{
	unsigned int mode;

	if (get_user(mode, p + 1))
		return -EFAULT;

	vesa_blank_mode = (mode < 4) ? mode : 0;
	return 0;
}