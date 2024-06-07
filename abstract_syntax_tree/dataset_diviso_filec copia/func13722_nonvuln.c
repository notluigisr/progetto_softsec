static int snd_nativeinstruments_control_put(struct snd_kcontrol *kcontrol,
					     struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	u8 oldval = (kcontrol->private_value >> 24) & 0xff;
	u8 newval = ucontrol->value.integer.value[0];
	int err;

	if (oldval == newval)
		return 0;

	kcontrol->private_value &= ~(0xff << 24);
	kcontrol->private_value |= (unsigned int)newval << 24;
	err = snd_ni_update_cur_val(list);
	return err < 0 ? err : 1;
}