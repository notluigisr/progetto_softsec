op_format(
    oparg_T	*oap,
    int		keep_cursor)		
{
    long	old_line_count = curbuf->b_ml.ml_line_count;

    
    
    curwin->w_cursor = oap->cursor_start;

    if (u_save((linenr_T)(oap->start.lnum - 1),
				       (linenr_T)(oap->end.lnum + 1)) == FAIL)
	return;
    curwin->w_cursor = oap->start;

    if (oap->is_VIsual)
	
	redraw_curbuf_later(INVERTED);

    if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
	
	curbuf->b_op_start = oap->start;

    
    
    if (keep_cursor)
	saved_cursor = oap->cursor_start;

    format_lines(oap->line_count, keep_cursor);

    
    
    
    if (oap->end_adjusted && curwin->w_cursor.lnum < curbuf->b_ml.ml_line_count)
	++curwin->w_cursor.lnum;
    beginline(BL_WHITE | BL_FIX);
    old_line_count = curbuf->b_ml.ml_line_count - old_line_count;
    msgmore(old_line_count);

    if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
	
	curbuf->b_op_end = curwin->w_cursor;

    if (keep_cursor)
    {
	curwin->w_cursor = saved_cursor;
	saved_cursor.lnum = 0;
    }

    if (oap->is_VIsual)
    {
	win_T	*wp;

	FOR_ALL_WINDOWS(wp)
	{
	    if (wp->w_old_cursor_lnum != 0)
	    {
		
		
		if (wp->w_old_cursor_lnum > wp->w_old_visual_lnum)
		    wp->w_old_cursor_lnum += old_line_count;
		else
		    wp->w_old_visual_lnum += old_line_count;
	    }
	}
    }
}