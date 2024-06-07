lspci_process(STREAM s)
{
	unsigned int pkglen;
	static char *rest = NULL;
	char *buf;

	pkglen = s->end - s->p;
	
	buf = xmalloc(pkglen + 1);
	STRNCPY(buf, (char *) s->p, pkglen + 1);
#if 0
	printf("STR");
	hexdump(s->p, pkglen);
#endif

	str_handle_lines(buf, &rest, lspci_process_line, NULL);
	xfree(buf);
}