ex_winpos(exarg_T *eap)
{
    int		x, y;
    char_u	*arg = eap->arg;
    char_u	*p;

    if (*arg == NUL)
    {
# if defined(FEAT_GUI) || defined(MSWIN)
#  ifdef FEAT_GUI
	if (gui.in_use && gui_mch_get_winpos(&x, &y) != FAIL)
#  else
	if (mch_get_winpos(&x, &y) != FAIL)
#  endif
	{
	    sprintf((char *)IObuff, _("STR"), x, y);
	    msg((char *)IObuff);
	}
	else
# endif
	    emsg(_("STR"));
    }
    else
    {
	x = getdigits(&arg);
	arg = skipwhite(arg);
	p = arg;
	y = getdigits(&arg);
	if (*p == NUL || *arg != NUL)
	{
	    emsg(_("STR"));
	    return;
	}
# ifdef FEAT_GUI
	if (gui.in_use)
	    gui_mch_set_winpos(x, y);
	else if (gui.starting)
	{
	    
	    gui_win_x = x;
	    gui_win_y = y;
	}
#  ifdef HAVE_TGETENT
	else
#  endif
# else
#  ifdef MSWIN
	    mch_set_winpos(x, y);
#  endif
# endif
# ifdef HAVE_TGETENT
	if (*T_CWP)
	    term_set_winpos(x, y);
# endif
    }
}