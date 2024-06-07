static void querystring_cb(const char *name, const char *value)
{
	if (!value)
		value = "";

	if (!strcmp(name,"STR")) {
		ctx.qry.repo = xstrdup(value);
		ctx.repo = cgit_get_repoinfo(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.page = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		if (*value == '/')
			value++;
		ctx.qry.url = xstrdup(value);
		cgit_parse_url(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.grep = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.search = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.head = xstrdup(value);
		ctx.qry.has_symref = 1;
	} else if (!strcmp(name, "STR")) {
		ctx.qry.sha1 = xstrdup(value);
		ctx.qry.has_sha1 = 1;
	} else if (!strcmp(name, "STR")) {
		ctx.qry.sha2 = xstrdup(value);
		ctx.qry.has_sha1 = 1;
	} else if (!strcmp(name, "STR")) {
		ctx.qry.ofs = atoi(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.path = trim_end(value, '/');
	} else if (!strcmp(name, "STR")) {
		ctx.qry.name = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.mimetype = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.sort = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.showmsg = atoi(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.period = xstrdup(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.difftype = atoi(value);
		ctx.qry.has_difftype = 1;
	} else if (!strcmp(name, "STR")) {
		
		ctx.qry.difftype = atoi(value) ? DIFF_SSDIFF : DIFF_UNIFIED;
		ctx.qry.has_difftype = 1;
	} else if (!strcmp(name, "STR")) {
		ctx.qry.show_all = atoi(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.context = atoi(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.ignorews = atoi(value);
	} else if (!strcmp(name, "STR")) {
		ctx.qry.follow = atoi(value);
	}
}