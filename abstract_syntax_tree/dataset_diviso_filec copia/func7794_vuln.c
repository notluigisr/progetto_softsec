mptctl_eventenable (unsigned long arg)
{
	struct mpt_ioctl_eventenable __user *uarg = (void __user *) arg;
	struct mpt_ioctl_eventenable	 karg;
	MPT_ADAPTER *ioc;
	int iocnum;

	if (copy_from_user(&karg, uarg, sizeof(struct mpt_ioctl_eventenable))) {
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
	if (ioc->events == NULL) {
		
		int sz = MPTCTL_EVENT_LOG_SIZE * sizeof(MPT_IOCTL_EVENTS);
		ioc->events = kzalloc(sz, GFP_KERNEL);
		if (!ioc->events) {
			printk(MYIOC_s_ERR_FMT
			    "STR",
			    ioc->name);
			return -ENOMEM;
		}
		ioc->alloc_total += sz;

		ioc->eventContext = 0;
        }

	
	ioc->eventTypes = karg.eventTypes;

	return 0;
}