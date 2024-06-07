int get_common_dir_noenv(struct strbuf *sb, const char *gitdir)
{
	struct strbuf data = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	int ret = 0;

	strbuf_addf(&path, "STR", gitdir);
	if (file_exists(path.buf)) {
		if (strbuf_read_file(&data, path.buf, 0) <= 0)
			die_errno(_("STR"), path.buf);
		while (data.len && (data.buf[data.len - 1] == '\n' ||
				    data.buf[data.len - 1] == '\r'))
			data.len--;
		data.buf[data.len] = '\0';
		strbuf_reset(&path);
		if (!is_absolute_path(data.buf))
			strbuf_addf(&path, "STR", gitdir);
		strbuf_addbuf(&path, &data);
		strbuf_add_real_path(sb, path.buf);
		ret = 1;
	} else {
		strbuf_addstr(sb, gitdir);
	}

	strbuf_release(&data);
	strbuf_release(&path);
	return ret;
}