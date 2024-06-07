redraw_buf_later(buf_T *buf, int type)
{
    win_T	*wp;

    FOR_ALL_WINDOWS(wp)
    {
	if (wp->w_buffer == buf)
	    redraw_win_later(wp, type);
    }
#if defined(FEAT_TERMINAL) && defined(FEAT_PROP_POPUP)
    
    if (curwin->w_buffer == buf)
	redraw_win_later(curwin, type);
#endif
}