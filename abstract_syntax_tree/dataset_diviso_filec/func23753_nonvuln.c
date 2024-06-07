find_var_in_ht(
    hashtab_T	*ht,
    int		htname,
    char_u	*varname,
    int		no_autoload)
{
    hashitem_T	*hi;

    if (*varname == NUL)
    {
	
	switch (htname)
	{
	    case 's': return &SCRIPT_SV(current_sctx.sc_sid)->sv_var;
	    case 'g': return &globvars_var;
	    case 'v': return &vimvars_var;
	    case 'b': return &curbuf->b_bufvar;
	    case 'w': return &curwin->w_winvar;
	    case 't': return &curtab->tp_winvar;
	    case 'l': return get_funccal_local_var();
	    case 'a': return get_funccal_args_var();
	}
	return NULL;
    }

    hi = hash_find(ht, varname);
    if (HASHITEM_EMPTY(hi))
    {
	
	
	
	
	if (ht == &globvarht && !no_autoload)
	{
	    
	    
	    if (!script_autoload(varname, FALSE) || aborting())
		return NULL;
	    hi = hash_find(ht, varname);
	}
	if (HASHITEM_EMPTY(hi))
	    return NULL;
    }
    return HI2DI(hi);
}