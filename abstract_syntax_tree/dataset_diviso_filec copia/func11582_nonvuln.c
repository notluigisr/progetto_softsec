win_alloc_firstwin(win_T *oldwin)
{
    curwin = win_alloc(NULL, FALSE);
    if (curwin == NULL)
	return FAIL;
    if (oldwin == NULL)
    {
	
	
	curbuf = buflist_new(NULL, NULL, 1L, BLN_LISTED);
	if (curwin == NULL || curbuf == NULL)
	    return FAIL;
	curwin->w_buffer = curbuf;
#ifdef FEAT_SYN_HL
	curwin->w_s = &(curbuf->b_s);
#endif
	curbuf->b_nwindows = 1;	
	curwin->w_alist = &global_alist;
	curwin_init();		
    }
    else
    {
	
	win_init(curwin, oldwin, 0);

	
	RESET_BINDING(curwin);
    }

    new_frame(curwin);
    if (curwin->w_frame == NULL)
	return FAIL;
    topframe = curwin->w_frame;
    topframe->fr_width = Columns;
    topframe->fr_height = Rows - p_ch;

    return OK;
}