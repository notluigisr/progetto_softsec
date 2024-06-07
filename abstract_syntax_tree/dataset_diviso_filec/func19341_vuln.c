win_goto(win_T *wp)
{
#ifdef FEAT_CONCEAL
    win_T	*owp = curwin;
#endif

#ifdef FEAT_PROP_POPUP
    if (ERROR_IF_ANY_POPUP_WINDOW)
	return;
    if (popup_is_popup(wp))
    {
	emsg(_(e_not_allowed_to_enter_popup_window));
	return;
    }
#endif
    if (text_locked())
    {
	beep_flush();
	text_locked_msg();
	return;
    }
    if (curbuf_locked())
	return;

    if (wp->w_buffer != curbuf)
	reset_VIsual_and_resel();
    else if (VIsual_active)
	wp->w_cursor = curwin->w_cursor;

#ifdef FEAT_GUI
    need_mouse_correct = TRUE;
#endif
    win_enter(wp, TRUE);

#ifdef FEAT_CONCEAL
    
    if (win_valid(owp) && owp->w_p_cole > 0 && !msg_scrolled)
	redrawWinline(owp, owp->w_cursor.lnum);
    if (curwin->w_p_cole > 0 && !msg_scrolled)
	need_cursor_line_redraw = TRUE;
#endif
}