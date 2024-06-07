eval_next_line(char_u *arg, evalarg_T *evalarg)
{
    garray_T	*gap = &evalarg->eval_ga;
    char_u	*line;

    if (arg != NULL)
    {
	if (*arg == NL)
	    return newline_skip_comments(arg);
	
	
	if (*skipwhite(arg) == '#')
	    *arg = NUL;
    }

    if (evalarg->eval_cookie != NULL)
	line = evalarg->eval_getline(0, evalarg->eval_cookie, 0,
							   GETLINE_CONCAT_ALL);
    else
	line = next_line_from_context(evalarg->eval_cctx, TRUE);
    if (line == NULL)
	return NULL;

    ++evalarg->eval_break_count;
    if (gap->ga_itemsize > 0 && ga_grow(gap, 1) == OK)
    {
	char_u *p = skipwhite(line);

	
	
	if (*p == NUL || vim9_comment_start(p))
	{
	    vim_free(line);
	    line = vim_strsave((char_u *)"");
	}

	((char_u **)gap->ga_data)[gap->ga_len] = line;
	++gap->ga_len;
    }
    else if (evalarg->eval_cookie != NULL)
    {
	vim_free(evalarg->eval_tofree);
	evalarg->eval_tofree = line;
    }

    
    
    evalarg->eval_using_cmdline = FALSE;
    return skipwhite(line);
}