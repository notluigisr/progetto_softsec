DelChar(NCURSES_SP_DCLx int count)
{
    TR(TRACE_UPDATE, ("STR",
		      (void *) SP_PARM, count,
		      (long) NewScreen(SP_PARM)->_cury,
		      (long) NewScreen(SP_PARM)->_curx));

    if (parm_dch) {
	TPUTS_TRACE("STR");
	NCURSES_SP_NAME(tputs) (NCURSES_SP_ARGx
				TPARM_1(parm_dch, count),
				1,
				NCURSES_SP_NAME(_nc_outch));
    } else {
	int n;

	for (n = 0; n < count; n++) {
	    NCURSES_PUTP2("STR", delete_character);
	}
    }
}