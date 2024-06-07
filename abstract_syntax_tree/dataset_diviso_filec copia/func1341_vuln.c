seamless_process(STREAM s)
{
	unsigned int pkglen;
	char *buf;

	pkglen = s->end - s->p;
	
	buf = xmalloc(pkglen + 1);
	STRNCPY(buf, (char *) s->p, pkglen + 1);
#if 0
	printf("STR");
	hexdump(s->p, pkglen);
#endif

	str_handle_lines(buf, &seamless_rest, seamless_line_handler, NULL);

	xfree(buf);
}