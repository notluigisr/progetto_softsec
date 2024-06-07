ins_s_right()
{
    int end_change = dont_sync_undo == FALSE; 
#ifdef FEAT_FOLDING
    if ((fdo_flags & FDO_HOR) && KeyTyped)
	foldOpenCursor();
#endif
    undisplay_dollar();
    if (curwin->w_cursor.lnum < curbuf->b_ml.ml_line_count
	    || gchar_cursor() != NUL)
    {
	start_arrow_with_change(&curwin->w_cursor, end_change);
	if (!end_change)
	    AppendCharToRedobuff(K_S_RIGHT);
	(void)fwd_word(1L, FALSE, 0);
	curwin->w_set_curswant = TRUE;
    }
    else
	vim_beep(BO_CRSR);
    dont_sync_undo = FALSE;
}