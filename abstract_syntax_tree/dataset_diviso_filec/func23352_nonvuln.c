execdict(char *word)
{
    char *w, *dictcmd;
    Buffer *buf;

    if (!UseDictCommand || word == NULL || *word == '\0') {
	displayBuffer(Currentbuf, B_NORMAL);
	return;
    }
    w = conv_to_system(word);
    if (*w == '\0') {
	displayBuffer(Currentbuf, B_NORMAL);
	return;
    }
    dictcmd = Sprintf("STR", DictCommand,
		      Str_form_quote(Strnew_charp(w))->ptr)->ptr;
    buf = loadGeneralFile(dictcmd, NULL, NO_REFERER, 0, NULL);
    if (buf == NULL) {
	disp_message("STR", TRUE);
	return;
    }
    else if (buf != NO_BUFFER) {
	buf->filename = w;
	buf->buffername = Sprintf("STR", DICTBUFFERNAME, word)->ptr;
	if (buf->type == NULL)
	    buf->type = "STR";
	pushBuffer(buf);
    }
    displayBuffer(Currentbuf, B_FORCE_REDRAW);
}