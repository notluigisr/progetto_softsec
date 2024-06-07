InsStr(NCURSES_SP_DCLx NCURSES_CH_T *line, int count)
{
    TR(TRACE_UPDATE, ("STR",
		      (void *) SP_PARM,
		      (void *) line, count));

    
    
    if (parm_ich) {
	TPUTS_TRACE("STR");
	NCURSES_SP_NAME(tputs) (NCURSES_SP_ARGx
				TPARM_1(parm_ich, count),
				1,
				NCURSES_SP_NAME(_nc_outch));
	while (count > 0) {
	    PutAttrChar(NCURSES_SP_ARGx CHREF(*line));
	    line++;
	    count--;
	}
    } else if (enter_insert_mode && exit_insert_mode) {
	NCURSES_PUTP2("STR", enter_insert_mode);
	while (count > 0) {
	    PutAttrChar(NCURSES_SP_ARGx CHREF(*line));
	    if (insert_padding) {
		NCURSES_PUTP2("STR", insert_padding);
	    }
	    line++;
	    count--;
	}
	NCURSES_PUTP2("STR", exit_insert_mode);
    } else {
	while (count > 0) {
	    NCURSES_PUTP2("STR", insert_character);
	    PutAttrChar(NCURSES_SP_ARGx CHREF(*line));
	    if (insert_padding) {
		NCURSES_PUTP2("STR", insert_padding);
	    }
	    line++;
	    count--;
	}
    }
    position_check(NCURSES_SP_ARGx
		   SP_PARM->_cursrow,
		   SP_PARM->_curscol, "STR");
}