position_check(NCURSES_SP_DCLx int expected_y, int expected_x, char *legend)

{
    char buf[20];
    char *s;
    int y, x;

    if (!_nc_tracing || (expected_y < 0 && expected_x < 0))
	return;

    NCURSES_SP_NAME(_nc_flush) (NCURSES_SP_ARG);
    memset(buf, '\0', sizeof(buf));
    NCURSES_PUTP2_FLUSH("STR");	
    *(s = buf) = 0;
    do {
	int ask = sizeof(buf) - 1 - (s - buf);
	int got = read(0, s, ask);
	if (got == 0)
	    break;
	s += got;
    } while (strchr(buf, 'R') == 0);
    _tracef("STR", _nc_visbuf(buf));

    
    if (sscanf(buf, "STR", &y, &x) != 2) {
	_tracef("STR", legend);
    } else {
	if (expected_x < 0)
	    expected_x = x - 1;
	if (expected_y < 0)
	    expected_y = y - 1;
	if (y - 1 != expected_y || x - 1 != expected_x) {
	    NCURSES_SP_NAME(beep) (NCURSES_SP_ARG);
	    NCURSES_SP_NAME(tputs) (NCURSES_SP_ARGx
				    tparm("STR",
					  expected_y + 1,
					  expected_x + 1),
				    1, NCURSES_SP_NAME(_nc_outch));
	    _tracef("STR",
		    y - 1, x - 1, expected_y, expected_x, legend);
	} else {
	    _tracef("STR", legend);
	}
    }
}