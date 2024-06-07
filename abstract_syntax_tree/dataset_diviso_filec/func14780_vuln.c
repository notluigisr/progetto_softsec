static ssize_t show_crash_notes(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct cpu *cpu = container_of(dev, struct cpu, dev);
	ssize_t rc;
	unsigned long long addr;
	int cpunum;

	cpunum = cpu->dev.id;

	
	addr = per_cpu_ptr_to_phys(per_cpu_ptr(crash_notes, cpunum));
	rc = sprintf(buf, "STR", addr);
	return rc;
}