static int cdrom_ioctl_play_trkind(struct cdrom_device_info *cdi,
		void __user *argp)
{
	struct cdrom_ti ti;
	int ret;

	cd_dbg(CD_DO_IOCTL, "STR");

	if (!CDROM_CAN(CDC_PLAY_AUDIO))
		return -ENOSYS;
	if (copy_from_user(&ti, argp, sizeof(ti)))
		return -EFAULT;

	ret = check_for_audio_disc(cdi, cdi->ops);
	if (ret)
		return ret;
	return cdi->ops->audio_ioctl(cdi, CDROMPLAYTRKIND, &ti);
}