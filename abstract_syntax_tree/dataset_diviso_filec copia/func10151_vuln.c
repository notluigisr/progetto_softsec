static int decode_tree_entry(struct tree_desc *desc, const char *buf, unsigned long size, struct strbuf *err)
{
	const char *path;
	unsigned int mode, len;

	if (size < 23 || buf[size - 21]) {
		strbuf_addstr(err, _("STR"));
		return -1;
	}

	path = get_mode(buf, &mode);
	if (!path) {
		strbuf_addstr(err, _("STR"));
		return -1;
	}
	if (!*path) {
		strbuf_addstr(err, _("STR"));
		return -1;
	}
	len = strlen(path) + 1;

	
	desc->entry.path = path;
	desc->entry.mode = canon_mode(mode);
	desc->entry.oid  = (const struct object_id *)(path + len);

	return 0;
}