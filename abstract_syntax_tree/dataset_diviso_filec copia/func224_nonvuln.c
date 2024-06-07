int verify_repository_format(const struct repository_format *format,
			     struct strbuf *err)
{
	if (GIT_REPO_VERSION_READ < format->version) {
		strbuf_addf(err, _("STR"),
			    GIT_REPO_VERSION_READ, format->version);
		return -1;
	}

	if (format->version >= 1 && format->unknown_extensions.nr) {
		int i;

		strbuf_addstr(err, _("STR"));

		for (i = 0; i < format->unknown_extensions.nr; i++)
			strbuf_addf(err, "STR",
				    format->unknown_extensions.items[i].string);
		return -1;
	}

	if (format->version == 0 && format->v1_only_extensions.nr) {
		int i;

		strbuf_addstr(err,
			      _("STR"));

		for (i = 0; i < format->v1_only_extensions.nr; i++)
			strbuf_addf(err, "STR",
				    format->v1_only_extensions.items[i].string);
		return -1;
	}

	return 0;
}