mptctl_mpt_command (unsigned long arg)
{
	struct mpt_ioctl_command __user *uarg = (void __user *) arg;
	struct mpt_ioctl_command  karg;
	MPT_ADAPTER	*ioc;
	int		iocnum;
	int		rc;


	if (copy_from_user(&karg, uarg, sizeof(struct mpt_ioctl_command))) {
		printk(KERN_ERR MYNAM "STR"
			"STR",
				__FILE__, __LINE__, uarg);
		return -EFAULT;
	}

	if (((iocnum = mpt_verify_adapter(karg.hdr.iocnum, &ioc)) < 0) ||
	    (ioc == NULL)) {
		printk(KERN_DEBUG MYNAM "STR",
				__FILE__, __LINE__, iocnum);
		return -ENODEV;
	}

	rc = mptctl_do_mpt_command (karg, &uarg->MF);

	return rc;
}