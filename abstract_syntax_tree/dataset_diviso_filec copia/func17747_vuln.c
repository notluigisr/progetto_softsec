static int handle_to_path(int mountdirfd, struct file_handle __user *ufh,
		   struct path *path)
{
	int retval = 0;
	struct file_handle f_handle;
	struct file_handle *handle = NULL;

	
	if (!capable(CAP_DAC_READ_SEARCH)) {
		retval = -EPERM;
		goto out_err;
	}
	if (copy_from_user(&f_handle, ufh, sizeof(struct file_handle))) {
		retval = -EFAULT;
		goto out_err;
	}
	if ((f_handle.handle_bytes > MAX_HANDLE_SZ) ||
	    (f_handle.handle_bytes == 0)) {
		retval = -EINVAL;
		goto out_err;
	}
	handle = kmalloc(sizeof(struct file_handle) + f_handle.handle_bytes,
			 GFP_KERNEL);
	if (!handle) {
		retval = -ENOMEM;
		goto out_err;
	}
	
	if (copy_from_user(handle, ufh,
			   sizeof(struct file_handle) +
			   f_handle.handle_bytes)) {
		retval = -EFAULT;
		goto out_handle;
	}

	retval = do_handle_to_path(mountdirfd, handle, path);

out_handle:
	kfree(handle);
out_err:
	return retval;
}