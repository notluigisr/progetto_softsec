DEFUN(newT, NEW_TAB, "STR")
{
    _newT();
    displayBuffer(Currentbuf, B_REDRAW_IMAGE);
}