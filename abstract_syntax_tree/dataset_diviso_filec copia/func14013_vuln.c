find_file_name_in_path(
    char_u	*ptr,
    int		len,
    int		options,
    long	count,
    char_u	*rel_fname)	
{
    char_u	*file_name;
    int		c;
# if defined(FEAT_FIND_ID) && defined(FEAT_EVAL)
    char_u	*tofree = NULL;

    if ((options & FNAME_INCL) && *curbuf->b_p_inex != NUL)
    {
	tofree = eval_includeexpr(ptr, len);
	if (tofree != NULL)
	{
	    ptr = tofree;
	    len = (int)STRLEN(ptr);
	}
    }
# endif

    if (options & FNAME_EXP)
    {
	file_name = find_file_in_path(ptr, len, options & ~FNAME_MESS,
							     TRUE, rel_fname);

# if defined(FEAT_FIND_ID) && defined(FEAT_EVAL)
	
	if (file_name == NULL
		&& !(options & FNAME_INCL) && *curbuf->b_p_inex != NUL)
	{
	    tofree = eval_includeexpr(ptr, len);
	    if (tofree != NULL)
	    {
		ptr = tofree;
		len = (int)STRLEN(ptr);
		file_name = find_file_in_path(ptr, len, options & ~FNAME_MESS,
							     TRUE, rel_fname);
	    }
	}
# endif
	if (file_name == NULL && (options & FNAME_MESS))
	{
	    c = ptr[len];
	    ptr[len] = NUL;
	    semsg(_("STR"), ptr);
	    ptr[len] = c;
	}

	
	
	while (file_name != NULL && --count > 0)
	{
	    vim_free(file_name);
	    file_name = find_file_in_path(ptr, len, options, FALSE, rel_fname);
	}
    }
    else
	file_name = vim_strnsave(ptr, len);

# if defined(FEAT_FIND_ID) && defined(FEAT_EVAL)
    vim_free(tofree);
# endif

    return file_name;
}