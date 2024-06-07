DEFUN(selBuf, SELECT, "STR")
{
    Buffer *buf;
    int ok;
    char cmd;

    ok = FALSE;
    do {
	buf = selectBuffer(Firstbuf, Currentbuf, &cmd);
	switch (cmd) {
	case 'B':
	    ok = TRUE;
	    break;
	case '\n':
	case ' ':
	    Currentbuf = buf;
	    ok = TRUE;
	    break;
	case 'D':
	    delBuffer(buf);
	    if (Firstbuf == NULL) {
		
		Firstbuf = nullBuffer();
		Currentbuf = Firstbuf;
	    }
	    break;
	case 'q':
	    qquitfm();
	    break;
	case 'Q':
	    quitfm();
	    break;
	}
    } while (!ok);

    for (buf = Firstbuf; buf != NULL; buf = buf->nextBuffer) {
	if (buf == Currentbuf)
	    continue;
#ifdef USE_IMAGE
	deleteImage(buf);
#endif
	if (clear_buffer)
	    tmpClearBuffer(buf);
    }
    displayBuffer(Currentbuf, B_FORCE_REDRAW);
}