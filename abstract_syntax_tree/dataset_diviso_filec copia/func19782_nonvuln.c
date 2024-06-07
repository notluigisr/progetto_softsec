static inline unsigned char vc_invert_attr(const struct vc_data *vc)
{
	if (!vc->vc_can_do_color)
		return vc->vc_attr ^ 0x08;

	if (vc->vc_hi_font_mask == 0x100)
		return   (vc->vc_attr & 0x11) |
			((vc->vc_attr & 0xe0) >> 4) |
			((vc->vc_attr & 0x0e) << 4);

	return   (vc->vc_attr & 0x88) |
		((vc->vc_attr & 0x70) >> 4) |
		((vc->vc_attr & 0x07) << 4);
}