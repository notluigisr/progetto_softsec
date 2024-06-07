NCURSES_SP_NAME(_nc_do_color) (NCURSES_SP_DCLx
			       int old_pair,
			       int pair,
			       int reverse,
			       NCURSES_SP_OUTC outc)
{
#ifdef USE_TERM_DRIVER
    CallDriver_4(SP_PARM, td_docolor, old_pair, pair, reverse, outc);
#else
    int fg = COLOR_DEFAULT;
    int bg = COLOR_DEFAULT;
    int old_fg = -1;
    int old_bg = -1;

    if (!ValidPair(SP_PARM, pair)) {
	return;
    } else if (pair != 0) {
	if (set_color_pair) {
	    TPUTS_TRACE("STR");
	    NCURSES_SP_NAME(tputs) (NCURSES_SP_ARGx
				    TPARM_1(set_color_pair, pair),
				    1, outc);
	    return;
	} else if (SP_PARM != 0) {
	    if (_nc_pair_content(SP_PARM, pair, &fg, &bg) == ERR)
		return;
	}
    }

    if (old_pair >= 0
	&& SP_PARM != 0
	&& _nc_pair_content(SP_PARM, old_pair, &old_fg, &old_bg) != ERR) {
	if ((isDefaultColor(fg) && !isDefaultColor(old_fg))
	    || (isDefaultColor(bg) && !isDefaultColor(old_bg))) {
#if NCURSES_EXT_FUNCS
	    
	    if (SP_PARM->_has_sgr_39_49
		&& isDefaultColor(old_bg)
		&& !isDefaultColor(old_fg)) {
		NCURSES_SP_NAME(tputs) (NCURSES_SP_ARGx "STR", 1, outc);
	    } else if (SP_PARM->_has_sgr_39_49
		       && isDefaultColor(old_fg)
		       && !isDefaultColor(old_bg)) {
		NCURSES_SP_NAME(tputs) (NCURSES_SP_ARGx "STR", 1, outc);
	    } else
#endif
		reset_color_pair(NCURSES_SP_ARG);
	}
    } else {
	reset_color_pair(NCURSES_SP_ARG);
	if (old_pair < 0 && pair <= 0)
	    return;
    }

#if NCURSES_EXT_FUNCS
    if (isDefaultColor(fg))
	fg = default_fg(NCURSES_SP_ARG);
    if (isDefaultColor(bg))
	bg = default_bg(NCURSES_SP_ARG);
#endif

    if (reverse) {
	int xx = fg;
	fg = bg;
	bg = xx;
    }

    TR(TRACE_ATTRS, ("STR", pair,
		     fg, bg));

    if (!isDefaultColor(fg)) {
	set_foreground_color(NCURSES_SP_ARGx fg, outc);
    }
    if (!isDefaultColor(bg)) {
	set_background_color(NCURSES_SP_ARGx bg, outc);
    }
#endif
}