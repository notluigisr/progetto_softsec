static int create_fixed_stream_quirk(struct snd_usb_audio *chip,
				     struct usb_interface *iface,
				     struct usb_driver *driver,
				     const struct snd_usb_audio_quirk *quirk)
{
	struct audioformat *fp;
	struct usb_host_interface *alts;
	struct usb_interface_descriptor *altsd;
	int stream, err;
	unsigned *rate_table = NULL;

	fp = kmemdup(quirk->data, sizeof(*fp), GFP_KERNEL);
	if (!fp) {
		usb_audio_err(chip, "STR");
		return -ENOMEM;
	}
	if (fp->nr_rates > MAX_NR_RATES) {
		kfree(fp);
		return -EINVAL;
	}
	if (fp->nr_rates > 0) {
		rate_table = kmemdup(fp->rate_table,
				     sizeof(int) * fp->nr_rates, GFP_KERNEL);
		if (!rate_table) {
			kfree(fp);
			return -ENOMEM;
		}
		fp->rate_table = rate_table;
	}

	stream = (fp->endpoint & USB_DIR_IN)
		? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;
	err = snd_usb_add_audio_stream(chip, stream, fp);
	if (err < 0)
		goto error;
	if (fp->iface != get_iface_desc(&iface->altsetting[0])->bInterfaceNumber ||
	    fp->altset_idx >= iface->num_altsetting) {
		err = -EINVAL;
		goto error;
	}
	alts = &iface->altsetting[fp->altset_idx];
	altsd = get_iface_desc(alts);
	if (altsd->bNumEndpoints < 1) {
		err = -EINVAL;
		goto error;
	}

	fp->protocol = altsd->bInterfaceProtocol;

	if (fp->datainterval == 0)
		fp->datainterval = snd_usb_parse_datainterval(chip, alts);
	if (fp->maxpacksize == 0)
		fp->maxpacksize = le16_to_cpu(get_endpoint(alts, 0)->wMaxPacketSize);
	usb_set_interface(chip->dev, fp->iface, 0);
	snd_usb_init_pitch(chip, fp->iface, alts, fp);
	snd_usb_init_sample_rate(chip, fp->iface, alts, fp, fp->rate_max);
	return 0;

 error:
	kfree(fp);
	kfree(rate_table);
	return err;
}