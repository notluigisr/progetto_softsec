do_modelines(int flags)
{
    linenr_T	lnum;
    int		nmlines;
    static int	entered = 0;

    if (!curbuf->b_p_ml || (nmlines = (int)p_mls) == 0)
	return;

    
    
    if (entered)
	return;

    ++entered;
    for (lnum = 1; curbuf->b_p_ml && lnum <= curbuf->b_ml.ml_line_count && lnum <= nmlines;
								       ++lnum)
	if (chk_modeline(lnum, flags) == FAIL)
	    nmlines = 0;

    for (lnum = curbuf->b_ml.ml_line_count; curbuf->b_p_ml && lnum > 0 && lnum > nmlines
		       && lnum > curbuf->b_ml.ml_line_count - nmlines; --lnum)
	if (chk_modeline(lnum, flags) == FAIL)
	    nmlines = 0;
    --entered;
}