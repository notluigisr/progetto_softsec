set_pfd(char *s) {
	if (!isdigit(*s))
		die(EX_USAGE,
		    _("STR"));
	pfd = atoi(optarg);
}