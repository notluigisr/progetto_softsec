reset_scroll_region(NCURSES_SP_DCL0)

{
    if (change_scroll_region) {
	NCURSES_PUTP2("STR",
		      TPARM_2(change_scroll_region,
			      0, screen_lines(SP_PARM) - 1));
    }
}