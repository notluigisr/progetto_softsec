op_shift(oparg_T *oap, int curs_top, int amount)
{
    long	    i;
    int		    first_char;
    int		    block_col = 0;

    if (u_save((linenr_T)(oap->start.lnum - 1),
				       (linenr_T)(oap->end.lnum + 1)) == FAIL)
	return;

    if (oap->block_mode)
	block_col = curwin->w_cursor.col;

    for (i = oap->line_count; --i >= 0; )
    {
	first_char = *ml_get_curline();
	if (first_char == NUL)				
	    curwin->w_cursor.col = 0;
	else if (oap->block_mode)
	    shift_block(oap, amount);
	else
	    
	    
	    if (first_char != '#' || !preprocs_left())
		shift_line(oap->op_type == OP_LSHIFT, p_sr, amount, FALSE);
	++curwin->w_cursor.lnum;
    }

    changed_lines(oap->start.lnum, 0, oap->end.lnum + 1, 0L);
    if (oap->block_mode)
    {
	curwin->w_cursor.lnum = oap->start.lnum;
	curwin->w_cursor.col = block_col;
    }
    else if (curs_top)	    
    {
	curwin->w_cursor.lnum = oap->start.lnum;
	beginline(BL_SOL | BL_FIX);   
    }
    else
	--curwin->w_cursor.lnum;	

#ifdef FEAT_FOLDING
    
    foldOpenCursor();
#endif


    if (oap->line_count > p_report)
    {
	char	    *op;
	char	    *msg_line_single;
	char	    *msg_line_plural;

	if (oap->op_type == OP_RSHIFT)
	    op = "STR";
	else
	    op = "STR";
	msg_line_single = NGETTEXT("STR",
					     "STR", amount);
	msg_line_plural = NGETTEXT("STR",
					    "STR", amount);
	vim_snprintf((char *)IObuff, IOSIZE,
		NGETTEXT(msg_line_single, msg_line_plural, oap->line_count),
		oap->line_count, op, amount);
	msg_attr_keep((char *)IObuff, 0, TRUE);
    }

    if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
    {
	
	curbuf->b_op_start = oap->start;
	curbuf->b_op_end.lnum = oap->end.lnum;
	curbuf->b_op_end.col = (colnr_T)STRLEN(ml_get(oap->end.lnum));
	if (curbuf->b_op_end.col > 0)
	    --curbuf->b_op_end.col;
    }
}