set_buffer_environ(Buffer *buf)
{
    static Buffer *prev_buf = NULL;
    static Line *prev_line = NULL;
    static int prev_pos = -1;
    Line *l;

    if (buf == NULL)
	return;
    if (buf != prev_buf) {
	set_environ("STR", buf->sourcefile);
	set_environ("STR", buf->filename);
	set_environ("STR", buf->buffername);
	set_environ("STR", parsedURL2Str(&buf->currentURL)->ptr);
	set_environ("STR");
#ifdef USE_M17N
	set_environ("STR", wc_ces_to_charset(buf->document_charset));
#endif
    }
    l = buf->currentLine;
    if (l && (buf != prev_buf || l != prev_line || buf->pos != prev_pos)) {
	Anchor *a;
	ParsedURL pu;
	char *s = GetWord(buf);
	set_environ("STR");
	a = retrieveCurrentAnchor(buf);
	if (a) {
	    parseURL2(a->url, &pu, baseURL(buf));
	    set_environ("STR", parsedURL2Str(&pu)->ptr);
	}
	else
	    set_environ("STR");
	a = retrieveCurrentImg(buf);
	if (a) {
	    parseURL2(a->url, &pu, baseURL(buf));
	    set_environ("STR", parsedURL2Str(&pu)->ptr);
	}
	else
	    set_environ("STR");
	a = retrieveCurrentForm(buf);
	if (a)
	    set_environ("STR", form2str((FormItemList *)a->url));
	else
	    set_environ("STR");
	set_environ("STR",
						l->real_linenumber)->ptr);
	set_environ("STR",
						  buf->currentColumn +
						  buf->cursorX + 1)->ptr);
    }
    else if (!l) {
	set_environ("STR");
	set_environ("STR");
	set_environ("STR");
	set_environ("STR");
	set_environ("STR");
	set_environ("STR");
    }
    prev_buf = buf;
    prev_line = l;
    prev_pos = buf->pos;
}