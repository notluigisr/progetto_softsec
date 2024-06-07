static int snd_usb_copy_string_desc(struct mixer_build *state,
				    int index, char *buf, int maxlen)
{
	int len = usb_string(state->chip->dev, index, buf, maxlen - 1);
	buf[len] = 0;
	return len;
}