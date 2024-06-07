static int cdrom_ioctl_select_disc(struct cdrom_device_info *cdi,
		unsigned long arg)
{
	cd_dbg(CD_DO_IOCTL, "STR");

	if (!CDROM_CAN(CDC_SELECT_DISC))
		return -ENOSYS;

	if (arg != CDSL_CURRENT && arg != CDSL_NONE) {
		if (arg >= cdi->capacity)
			return -EINVAL;
	}

	
	if (cdi->ops->select_disc)
		return cdi->ops->select_disc(cdi, arg);

	cd_dbg(CD_CHANGER, "STR");
	return cdrom_select_disc(cdi, arg);
}