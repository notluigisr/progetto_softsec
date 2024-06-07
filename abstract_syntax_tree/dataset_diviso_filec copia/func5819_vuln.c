static ssize_t nports_show(struct device *dev, struct device_attribute *attr,
			   char *out)
{
	char *s = out;

	
	out += sprintf(out, "STR", VHCI_PORTS * vhci_num_controllers);
	return out - s;
}