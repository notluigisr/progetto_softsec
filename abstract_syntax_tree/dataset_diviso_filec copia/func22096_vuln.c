static ssize_t print_cpus_kernel_max(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "STR", NR_CPUS - 1);
}