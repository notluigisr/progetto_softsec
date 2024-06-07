ex_win_close(
    int		forceit,
    win_T	*win,
    tabpage_T	*tp)		
{
    int		need_hide;
    buf_T	*buf = win->w_buffer;

    
    if (win == aucmd_win)
    {
	emsg(_(e_autocmd_close));
	return;
    }

    need_hide = (bufIsChanged(buf) && buf->b_nwindows <= 1);
    if (need_hide && !buf_hide(buf) && !forceit)
    {
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
	if ((p_confirm || (cmdmod.cmod_flags & CMOD_CONFIRM)) && p_write)
	{
	    bufref_T bufref;

	    set_bufref(&bufref, buf);
	    dialog_changed(buf, FALSE);
	    if (bufref_valid(&bufref) && bufIsChanged(buf))
		return;
	    need_hide = FALSE;
	}
	else
#endif
	{
	    no_write_message();
	    return;
	}
    }

#ifdef FEAT_GUI
    need_mouse_correct = TRUE;
#endif

    
    if (tp == NULL)
	win_close(win, !need_hide && !buf_hide(buf));
    else
	win_close_othertab(win, !need_hide && !buf_hide(buf), tp);
}