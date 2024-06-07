ff_get_visited_list(
    char_u			*filename,
    ff_visited_list_hdr_T	**list_headp)
{
    ff_visited_list_hdr_T  *retptr = NULL;

    
    if (*list_headp != NULL)
    {
	retptr = *list_headp;
	while (retptr != NULL)
	{
	    if (fnamecmp(filename, retptr->ffvl_filename) == 0)
	    {
#ifdef FF_VERBOSE
		if (p_verbose >= 5)
		{
		    verbose_enter_scroll();
		    smsg("STR",
								    filename);
		    
		    msg_puts("STR");
		    verbose_leave_scroll();
		}
#endif
		return retptr;
	    }
	    retptr = retptr->ffvl_next;
	}
    }

#ifdef FF_VERBOSE
    if (p_verbose >= 5)
    {
	verbose_enter_scroll();
	smsg("STR", filename);
	
	msg_puts("STR");
	verbose_leave_scroll();
    }
#endif

    
    retptr = ALLOC_ONE(ff_visited_list_hdr_T);
    if (retptr == NULL)
	return NULL;

    retptr->ffvl_visited_list = NULL;
    retptr->ffvl_filename = vim_strsave(filename);
    if (retptr->ffvl_filename == NULL)
    {
	vim_free(retptr);
	return NULL;
    }
    retptr->ffvl_next = *list_headp;
    *list_headp = retptr;

    return retptr;
}