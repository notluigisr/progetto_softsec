static int cdrom_mrw_open_write(struct cdrom_device_info *cdi)
{
	disc_information di;
	int ret;

	
	if (cdrom_mrw_set_lba_space(cdi, MRW_LBA_DMA)) {
		pr_err("STR");
		return 1;
	}

	ret = cdrom_get_disc_info(cdi, &di);
	if (ret < 0 || ret < offsetof(typeof(di),disc_type))
		return 1;

	if (!di.erasable)
		return 1;

	
	ret = 0;
	pr_info("STR", mrw_format_status[di.mrw_status]);
	if (!di.mrw_status)
		ret = 1;
	else if (di.mrw_status == CDM_MRW_BGFORMAT_INACTIVE &&
			mrw_format_restart)
		ret = cdrom_mrw_bgformat(cdi, 1);

	return ret;
}