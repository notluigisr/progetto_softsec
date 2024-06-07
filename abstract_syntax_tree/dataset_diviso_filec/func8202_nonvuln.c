rename_buffer(char_u *new_fname)
{
    char_u	*fname, *sfname, *xfname;
    buf_T	*buf;

    buf = curbuf;
    apply_autocmds(EVENT_BUFFILEPRE, NULL, NULL, FALSE, curbuf);
    
    if (buf != curbuf)
	return FAIL;
#ifdef FEAT_EVAL
    if (aborting())	    
	return FAIL;
#endif
    
    fname = curbuf->b_ffname;
    sfname = curbuf->b_sfname;
    xfname = curbuf->b_fname;
    curbuf->b_ffname = NULL;
    curbuf->b_sfname = NULL;
    if (setfname(curbuf, new_fname, NULL, TRUE) == FAIL)
    {
	curbuf->b_ffname = fname;
	curbuf->b_sfname = sfname;
	return FAIL;
    }
    curbuf->b_flags |= BF_NOTEDITED;
    if (xfname != NULL && *xfname != NUL)
    {
	buf = buflist_new(fname, xfname, curwin->w_cursor.lnum, 0);
	if (buf != NULL && !cmdmod.keepalt)
	    curwin->w_alt_fnum = buf->b_fnum;
    }
    vim_free(fname);
    vim_free(sfname);
    apply_autocmds(EVENT_BUFFILEPOST, NULL, NULL, FALSE, curbuf);

    
    DO_AUTOCHDIR;
    return OK;
}