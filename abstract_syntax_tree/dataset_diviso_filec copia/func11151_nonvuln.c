sd_show_protection_type(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);

	return snprintf(buf, 20, "STR", sdkp->protection_type);
}