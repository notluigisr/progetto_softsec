static void vidioc_fill_name(char *buf, int len, int nr)
{
	if (card_label[nr] != NULL) {
		snprintf(buf, len, card_label[nr]);
	} else {
		snprintf(buf, len, "STR", nr);
	}
}