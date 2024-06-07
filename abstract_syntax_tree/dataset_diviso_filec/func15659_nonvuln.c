win_col_off(win_T *wp)
{
    return (((wp->w_p_nu || wp->w_p_rnu) ? number_width(wp) + 1 : 0)
#ifdef FEAT_CMDWIN
	    + (cmdwin_type == 0 || wp != curwin ? 0 : 1)
#endif
#ifdef FEAT_FOLDING
	    + wp->w_p_fdc
#endif
#ifdef FEAT_SIGNS
	    + (signcolumn_on(wp) ? 2 : 0)
#endif
	   );
}