win_valid(win_T *win)
{
    win_T	*wp;

    if (win == NULL)
	return FALSE;
    FOR_ALL_WINDOWS(wp)
	if (wp == win)
	    return TRUE;
    return win_valid_popup(win);
}