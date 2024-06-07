drv_initpair(TERMINAL_CONTROL_BLOCK * TCB, int pair, int f, int b)
{
    SCREEN *sp;

    AssertTCB();
    SetSP();

    if ((initialize_pair != NULL) && InPalette(f) && InPalette(b)) {
	const color_t *tp = InfoOf(sp).defaultPalette;

	TR(TRACE_ATTRS,
	   ("STR",
	    pair,
	    tp[f].red, tp[f].green, tp[f].blue,
	    tp[b].red, tp[b].green, tp[b].blue));

	NCURSES_PUTP2("STR",
		      TPARM_7(initialize_pair,
			      pair,
			      tp[f].red, tp[f].green, tp[f].blue,
			      tp[b].red, tp[b].green, tp[b].blue));
    }
}