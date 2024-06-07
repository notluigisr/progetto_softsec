mptctl_eventreport (unsigned long arg)
{
	struct mpt_ioctl_eventreport __user *uarg = (void __user *) arg;
	struct mpt_ioctl_eventreport	 karg;
	MPT_ADAPTER		 *ioc;
	int			 iocnum;
	int			 numBytes, maxEvents, max;

	if (copy_from_user(&karg, uarg, sizeof(struct mpt_ioctl_eventreport))) {
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

	numBytes = karg.hdr.maxDataSize - sizeof(mpt_ioctl_header);
	maxEvents = numBytes/sizeof(MPT_IOCTL_EVENTS);


	max = MPTCTL_EVENT_LOG_SIZE < maxEvents ? MPTCTL_EVENT_LOG_SIZE : maxEvents;

	
	if ((max < 1) || !ioc->events)
		return -ENODATA;

	
	ioc->aen_event_read_flag=0;

	
	numBytes = max * sizeof(MPT_IOCTL_EVENTS);
	if (copy_to_user(uarg->eventData, ioc->events, numBytes)) {
		printk(MYIOC_s_ERR_FMT "STR"
			"STR",
			ioc->name, __FILE__, __LINE__, ioc->events);
		return -EFAULT;
	}

	return 0;
}