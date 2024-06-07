static int set_sample_rate_v1(struct snd_usb_audio *chip, int iface,
			      struct usb_host_interface *alts,
			      struct audioformat *fmt, int rate)
{
	struct usb_device *dev = chip->dev;
	unsigned int ep;
	unsigned char data[3];
	int err, crate;

	ep = get_endpoint(alts, 0)->bEndpointAddress;

	
	if (!(fmt->attributes & UAC_EP_CS_ATTR_SAMPLE_RATE))
		return 0;

	data[0] = rate;
	data[1] = rate >> 8;
	data[2] = rate >> 16;
	if ((err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC_SET_CUR,
				   USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_DIR_OUT,
				   UAC_EP_CS_ATTR_SAMPLE_RATE << 8, ep,
				   data, sizeof(data))) < 0) {
		dev_err(&dev->dev, "STR",
			iface, fmt->altsetting, rate, ep);
		return err;
	}

	
	if (snd_usb_get_sample_rate_quirk(chip))
		return 0;

	if ((err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC_GET_CUR,
				   USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_DIR_IN,
				   UAC_EP_CS_ATTR_SAMPLE_RATE << 8, ep,
				   data, sizeof(data))) < 0) {
		dev_err(&dev->dev, "STR",
			iface, fmt->altsetting, ep);
		return 0; 
	}

	crate = data[0] | (data[1] << 8) | (data[2] << 16);
	if (crate != rate) {
		dev_warn(&dev->dev, "STR", crate, rate);
		
	}

	return 0;
}