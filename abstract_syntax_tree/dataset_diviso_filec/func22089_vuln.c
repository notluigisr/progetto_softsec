nv_gotofile(cmdarg_T *cap)
{
    char_u	*ptr;
    linenr_T	lnum = -1;

    if (text_locked())
    {
	clearopbeep(cap->oap);
	text_locked_msg();
	return;
    }
    if (curbuf_locked())
    {
	clearop(cap->oap);
	return;
    }
#ifdef FEAT_PROP_POPUP
    if (ERROR_IF_TERM_POPUP_WINDOW)
	return;
#endif

    ptr = grab_file_name(cap->count1, &lnum);

    if (ptr != NULL)
    {
	
	if (curbufIsChanged() && curbuf->b_nwindows <= 1 && !buf_hide(curbuf))
	    (void)autowrite(curbuf, FALSE);
	setpcmark();
	if (do_ecmd(0, ptr, NULL, NULL, ECMD_LAST,
				buf_hide(curbuf) ? ECMD_HIDE : 0, curwin) == OK
		&& cap->nchar == 'F' && lnum >= 0)
	{
	    curwin->w_cursor.lnum = lnum;
	    check_cursor_lnum();
	    beginline(BL_SOL | BL_FIX);
	}
	vim_free(ptr);
    }
    else
	clearop(cap->oap);
}