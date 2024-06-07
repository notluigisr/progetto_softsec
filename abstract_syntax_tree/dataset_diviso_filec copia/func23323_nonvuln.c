cursorDown(Buffer *buf, int n)
{
    Line *l = buf->currentLine;
    if (buf->firstLine == NULL)
	return;
    while (buf->currentLine->next && buf->currentLine->next->bpos)
	cursorDown0(buf, n);
    if (buf->currentLine == buf->lastLine) {
	gotoLine(buf, l->linenumber);
	arrangeLine(buf);
	return;
    }
    cursorDown0(buf, n);
    while (buf->currentLine->next && buf->currentLine->next->bpos &&
	   buf->currentLine->bwidth + buf->currentLine->width <
	   buf->currentColumn + buf->visualpos)
	cursorDown0(buf, n);
}