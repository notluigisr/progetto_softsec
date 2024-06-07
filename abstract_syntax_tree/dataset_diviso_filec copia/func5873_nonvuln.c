NCURSES_SP_NAME(_nc_mvcur_resume) (NCURSES_SP_DCL0)

{
    if (!SP_PARM || !IsTermInfo(SP_PARM))
	return;

    
    if (enter_ca_mode) {
	NCURSES_PUTP2("STR", enter_ca_mode);
    }

    
    reset_scroll_region(NCURSES_SP_ARG);
    SP_PARM->_cursrow = SP_PARM->_curscol = -1;

    
    if (SP_PARM->_cursor != -1) {
	int cursor = SP_PARM->_cursor;
	SP_PARM->_cursor = -1;
	NCURSES_SP_NAME(curs_set) (NCURSES_SP_ARGx cursor);
    }
}