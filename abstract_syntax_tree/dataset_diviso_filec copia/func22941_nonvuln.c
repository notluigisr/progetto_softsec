DEFUN(linbeg, LINE_BEGIN, "STR")
{
    if (Currentbuf->firstLine == NULL)
	return;
    while (Currentbuf->currentLine->prev && Currentbuf->currentLine->bpos)
	cursorUp0(Currentbuf, 1);
    Currentbuf->pos = 0;
    arrangeCursor(Currentbuf);
    displayBuffer(Currentbuf, B_NORMAL);
}