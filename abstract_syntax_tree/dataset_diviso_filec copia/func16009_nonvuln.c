static void rgb_foreground(struct vc_data *vc, const struct rgb *c)
{
	u8 hue = 0, max = max3(c->r, c->g, c->b);

	if (c->r > max / 2)
		hue |= 4;
	if (c->g > max / 2)
		hue |= 2;
	if (c->b > max / 2)
		hue |= 1;

	if (hue == 7 && max <= 0x55) {
		hue = 0;
		vc->state.intensity = VCI_BOLD;
	} else if (max > 0xaa)
		vc->state.intensity = VCI_BOLD;
	else
		vc->state.intensity = VCI_NORMAL;

	vc->state.color = (vc->state.color & 0xf0) | hue;
}