mptctl_fw_download(unsigned long arg)
{
	struct mpt_fw_xfer __user *ufwdl = (void __user *) arg;
	struct mpt_fw_xfer	 kfwdl;

	if (copy_from_user(&kfwdl, ufwdl, sizeof(struct mpt_fw_xfer))) {
		printk(KERN_ERR MYNAM "STR"
				"STR",
				__FILE__, __LINE__, ufwdl);
		return -EFAULT;
	}

	return mptctl_do_fw_download(kfwdl.iocnum, kfwdl.bufp, kfwdl.fwlen);
}