static ssize_t set_cmci_disabled(struct device *s,
				 struct device_attribute *attr,
				 const char *buf, size_t size)
{
	u64 new;

	if (kstrtou64(buf, 0, &new) < 0)
		return -EINVAL;

	if (mca_cfg.cmci_disabled ^ !!new) {
		if (new) {
			
			on_each_cpu(mce_disable_cmci, NULL, 1);
			mca_cfg.cmci_disabled = true;
		} else {
			
			mca_cfg.cmci_disabled = false;
			on_each_cpu(mce_enable_ce, NULL, 1);
		}
	}
	return size;
}