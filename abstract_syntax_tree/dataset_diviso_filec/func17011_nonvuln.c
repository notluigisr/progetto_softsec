update_curswant_force(void)
{
    validate_virtcol();
    curwin->w_curswant = curwin->w_virtcol
#ifdef FEAT_PROP_POPUP
	- curwin->w_virtcol_first_char
#endif
	;
    curwin->w_set_curswant = FALSE;
}