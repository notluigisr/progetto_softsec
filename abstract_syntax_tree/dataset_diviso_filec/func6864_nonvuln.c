static const char *chdir_to_parent(const char *node, char **resbuf)
{
	char *tmp, *res;
	const char *parent;
	char buf[65536];

	*resbuf = xstrdup(node);

	tmp = strrchr(*resbuf, '/');
	if (!tmp)
		die (2, _("STR"), node);

	if (tmp != *resbuf) {
		*tmp = '\0';
		res = tmp + 1;
		parent = *resbuf;
	} else if (tmp[1] != '\0') {
		res = tmp + 1;
		parent = "STR";
	} else {
		res = "STR";
		parent = "STR";
	}

	if (chdir(parent) == -1)
		die (2, _("STR"),
					parent, strerror(errno));

	if (!getcwd(buf, sizeof(buf)))
		die (2, _("STR"),
			strerror(errno));

	if (strcmp(buf, parent) != 0)
		die (2, _("STR"), parent, buf);

	if (verbose)
		printf(_("STR"), res);

	return res;
}