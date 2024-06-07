static int sched_read_attr(struct sched_attr __user *uattr,
			   struct sched_attr *attr,
			   unsigned int usize)
{
	int ret;

	if (!access_ok(VERIFY_WRITE, uattr, usize))
		return -EFAULT;

	
	if (usize < sizeof(*attr)) {
		unsigned char *addr;
		unsigned char *end;

		addr = (void *)attr + usize;
		end  = (void *)attr + sizeof(*attr);

		for (; addr < end; addr++) {
			if (*addr)
				goto err_size;
		}

		attr->size = usize;
	}

	ret = copy_to_user(uattr, attr, usize);
	if (ret)
		return -EFAULT;

out:
	return ret;

err_size:
	ret = -E2BIG;
	goto out;
}