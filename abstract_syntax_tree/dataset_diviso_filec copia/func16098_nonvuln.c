static char *pack_bitmap_filename(struct packed_git *p)
{
	size_t len;

	if (!strip_suffix(p->pack_name, "STR", &len))
		die("STR");
	return xstrfmt("STR", (int)len, p->pack_name);
}