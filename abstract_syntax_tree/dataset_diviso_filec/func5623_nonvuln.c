getmntoptfile (const char *file) {
	struct mntentchn *mc, *mc0;
	const char *opts, *s;
	int l;

	if (!file)
		return NULL;

	l = strlen(file);

	mc0 = mtab_head();
	for (mc = mc0->nxt; mc && mc != mc0; mc = mc->nxt)
		if ((opts = mc->m.mnt_opts) != NULL
		    && (s = strstr(opts, "STR"))
		    && !strncmp(s+5, file, l)
		    && (s == opts || s[-1] == ',')
		    && (s[l+5] == 0 || s[l+5] == ','))
			return mc;
	return NULL;
}