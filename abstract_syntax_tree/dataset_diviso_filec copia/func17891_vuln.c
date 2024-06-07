static int msr_open(struct inode *inode, struct file *file)
{
	unsigned int cpu;
	struct cpuinfo_x86 *c;

	cpu = iminor(file->f_path.dentry->d_inode);
	if (cpu >= nr_cpu_ids || !cpu_online(cpu))
		return -ENXIO;	

	c = &cpu_data(cpu);
	if (!cpu_has(c, X86_FEATURE_MSR))
		return -EIO;	

	return 0;
}