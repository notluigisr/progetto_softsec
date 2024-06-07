static int compat_standard_to_user(void __user *dst, void *src)
{
	compat_int_t cv = *(int *)src;

	if (cv > 0)
		cv -= compat_calc_jump(cv);
	return copy_to_user(dst, &cv, sizeof(cv)) ? -EFAULT : 0;
}