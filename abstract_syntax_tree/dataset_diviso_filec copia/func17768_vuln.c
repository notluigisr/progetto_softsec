static int mptctl_do_reset(unsigned long arg)
{
	struct mpt_ioctl_diag_reset __user *urinfo = (void __user *) arg;
	struct mpt_ioctl_diag_reset krinfo;
	MPT_ADAPTER		*iocp;

	if (copy_from_user(&krinfo, urinfo, sizeof(struct mpt_ioctl_diag_reset))) {
		printk(KERN_ERR MYNAM "STR"
				"STR",
				__FILE__, __LINE__, urinfo);
		return -EFAULT;
	}

	if (mpt_verify_adapter(krinfo.hdr.iocnum, &iocp) < 0) {
		printk(KERN_DEBUG MYNAM "STR",
				__FILE__, __LINE__, krinfo.hdr.iocnum);
		return -ENODEV; 
	}

	dctlprintk(iocp, printk(MYIOC_s_DEBUG_FMT "STR",
	    iocp->name));

	if (mpt_HardResetHandler(iocp, CAN_SLEEP) != 0) {
		printk (MYIOC_s_ERR_FMT "STR",
			iocp->name, __FILE__, __LINE__);
		return -1;
	}

	return 0;
}