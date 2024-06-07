mptctl_readtest (unsigned long arg)
{
	struct mpt_ioctl_test __user *uarg = (void __user *) arg;
	struct mpt_ioctl_test	 karg;
	MPT_ADAPTER *ioc;
	int iocnum;

	if (copy_from_user(&karg, uarg, sizeof(struct mpt_ioctl_test))) {
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
	

#ifdef MFCNT
	karg.chip_type = ioc->mfcnt;
#else
	karg.chip_type = ioc->pcidev->device;
#endif
	strncpy (karg.name, ioc->name, MPT_MAX_NAME);
	karg.name[MPT_MAX_NAME-1]='\0';
	strncpy (karg.product, ioc->prod_name, MPT_PRODUCT_LENGTH);
	karg.product[MPT_PRODUCT_LENGTH-1]='\0';

	
	if (copy_to_user((char __user *)arg, &karg, sizeof(struct mpt_ioctl_test))) {
		printk(MYIOC_s_ERR_FMT "STR"
			"STR",
			ioc->name, __FILE__, __LINE__, uarg);
		return -EFAULT;
	}

	return 0;
}