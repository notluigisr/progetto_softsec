mptctl_replace_fw (unsigned long arg)
{
	struct mpt_ioctl_replace_fw __user *uarg = (void __user *) arg;
	struct mpt_ioctl_replace_fw	 karg;
	MPT_ADAPTER		 *ioc;
	int			 iocnum;
	int			 newFwSize;

	if (copy_from_user(&karg, uarg, sizeof(struct mpt_ioctl_replace_fw))) {
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

	dctlprintk(ioc, printk(MYIOC_s_DEBUG_FMT "STR",
	    ioc->name));
	
	if (ioc->cached_fw == NULL)
		return 0;

	mpt_free_fw_memory(ioc);

	
	newFwSize = ALIGN(karg.newImageSize, 4);

	mpt_alloc_fw_memory(ioc, newFwSize);
	if (ioc->cached_fw == NULL)
		return -ENOMEM;

	
	if (copy_from_user(ioc->cached_fw, uarg->newImage, newFwSize)) {
		printk(MYIOC_s_ERR_FMT "STR"
				"STR"
				"STR", ioc->name, __FILE__, __LINE__, uarg);
		mpt_free_fw_memory(ioc);
		return -EFAULT;
	}

	
	ioc->facts.FWImageSize = newFwSize;
	return 0;
}