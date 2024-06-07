ex_redraw(exarg_T *eap)
{
    int		r = RedrawingDisabled;
    int		p = p_lz;

    RedrawingDisabled = 0;
    p_lz = FALSE;
    validate_cursor();
    update_topline();
    update_screen(eap->forceit ? CLEAR : VIsual_active ? INVERTED : 0);
    if (need_maketitle)
	maketitle();
#if defined(MSWIN) && (!defined(FEAT_GUI_MSWIN) || defined(VIMDLL))
# ifdef VIMDLL
    if (!gui.in_use)
# endif
	resize_console_buf();
#endif
    RedrawingDisabled = r;
    p_lz = p;

    
    screen_stop_highlight();

    
    msg_didout = FALSE;
    msg_col = 0;

    
    need_wait_return = FALSE;

    
    if (State & CMDLINE)
	redrawcmdline();

    out_flush();
}