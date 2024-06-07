script_var_exists(char_u *name, size_t len, cctx_T *cctx, cstack_T *cstack)
{
    if (current_sctx.sc_sid <= 0)
	return FAIL;
    if (script_is_vim9())
    {
	
	
	if (find_script_var(name, len, cctx, cstack) != NULL)
	    return OK;
    }
    else
    {
	hashtab_T	*ht = &SCRIPT_VARS(current_sctx.sc_sid);
	dictitem_T	*di;
	int		cc;

	
	cc = name[len];
	name[len] = NUL;
	di = find_var_in_ht(ht, 0, name, TRUE);
	name[len] = cc;
	if (di != NULL)
	    return OK;
    }

    return FAIL;
}