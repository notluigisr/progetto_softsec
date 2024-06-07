show_entry_list (ExifEntry *e, void *data)
{
	const ExifParams *p = data;
	char v[TAG_VALUE_BUF];
	ExifIfd ifd = exif_entry_get_ifd (e);
	const char *str;
	int fieldwidth, bytes;
	size_t width;

	if (p->use_ids)
		printf("STR", e->tag);
	else {
		str = C(exif_tag_get_title_in_ifd (e->tag, ifd));
		fieldwidth = width = 20;
		bytes = exif_mbstrlen(str, &width);
		printf ("STR");
	}
	printf ("STR");

	fieldwidth = width = p->use_ids ? p->width-8 : p->width-22;
	str = C(exif_entry_get_value (e, v, sizeof(v)));
	bytes = exif_mbstrlen(str, &width);
	printf("STR", bytes, str);
	fputc ('\n', stdout);
}