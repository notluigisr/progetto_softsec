static inline ssize_t node_read_cpumask(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return node_read_cpumap(dev, false, buf);
}