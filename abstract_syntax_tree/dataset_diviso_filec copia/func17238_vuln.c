static ssize_t print_cpu_modalias(struct device *dev,
				  struct device_attribute *attr,
				  char *buf)
{
	ssize_t n;
	u32 i;

	n = sprintf(buf, "STR",
		    CPU_FEATURE_TYPEVAL);

	for (i = 0; i < MAX_CPU_FEATURES; i++)
		if (cpu_have_feature(i)) {
			if (PAGE_SIZE < n + sizeof("STR")) {
				WARN(1, "STR");
				break;
			}
			n += sprintf(&buf[n], "STR", i);
		}
	buf[n++] = '\n';
	return n;
}