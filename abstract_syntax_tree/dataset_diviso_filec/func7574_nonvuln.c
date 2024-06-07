static int snd_c400_create_effect_vol_ctls(struct usb_mixer_interface *mixer)
{
	char name[64];
	unsigned int cmask;
	int chan, err;
	int num_outs = 0;
	int num_ins = 0;

	const unsigned int id = 0x42;
	const int val_type = USB_MIXER_S16;
	const int control = 1;

	switch (mixer->chip->usb_id) {
	case USB_ID(0x0763, 0x2030):
		num_outs = 6;
		num_ins = 4;
		break;
	case USB_ID(0x0763, 0x2031):
		num_outs = 8;
		num_ins = 6;
		break;
	}

	for (chan = 0; chan < num_outs + num_ins; chan++) {
		if (chan < num_outs) {
			snprintf(name, sizeof(name),
				"STR",
				chan + 1);
		} else {
			snprintf(name, sizeof(name),
				"STR",
				chan - num_outs + 1);
		}

		cmask = (chan == 0) ? 0 : 1 << (chan - 1);
		err = snd_create_std_mono_ctl(mixer, id, control,
						cmask, val_type, name,
						&snd_usb_mixer_vol_tlv);
		if (err < 0)
			return err;
	}

	return 0;
}