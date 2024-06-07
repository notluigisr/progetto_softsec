int snd_usb_init_sample_rate(struct snd_usb_audio *chip, int iface,
			     struct usb_host_interface *alts,
			     struct audioformat *fmt, int rate)
{
	switch (fmt->protocol) {
	case UAC_VERSION_1:
	default:
		return set_sample_rate_v1(chip, iface, alts, fmt, rate);

	case UAC_VERSION_2:
		return set_sample_rate_v2(chip, iface, alts, fmt, rate);
	}
}