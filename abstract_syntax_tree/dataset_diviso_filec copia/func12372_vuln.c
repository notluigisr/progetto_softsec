static int opl3_load_patch(int dev, int format, const char __user *addr,
		int offs, int count, int pmgr_flag)
{
	struct sbi_instrument ins;

	if (count <sizeof(ins))
	{
		printk(KERN_WARNING "STR");
		return -EINVAL;
	}

	
	if(copy_from_user(&((char *) &ins)[offs], addr + offs, sizeof(ins) - offs))
		return -EFAULT;

	if (ins.channel < 0 || ins.channel >= SBFM_MAXINSTR)
	{
		printk(KERN_WARNING "STR", ins.channel);
		return -EINVAL;
	}
	ins.key = format;

	return store_instr(ins.channel, &ins);
}