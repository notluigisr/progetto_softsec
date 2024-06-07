f_getwininfo(typval_T *argvars, typval_T *rettv)
{
    tabpage_T	*tp;
    win_T	*wp = NULL, *wparg = NULL;
    dict_T	*d;
    short	tabnr = 0, winnr;

    if (rettv_list_alloc(rettv) != OK)
	return;

    if (argvars[0].v_type != VAR_UNKNOWN)
    {
	wparg = win_id2wp(argvars);
	if (wparg == NULL)
	    return;
    }

    
    FOR_ALL_TABPAGES(tp)
    {
	tabnr++;
	winnr = 0;
	FOR_ALL_WINDOWS_IN_TAB(tp, wp)
	{
	    winnr++;
	    if (wparg != NULL && wp != wparg)
		continue;
	    d = get_win_info(wp, tabnr, winnr);
	    if (d != NULL)
		list_append_dict(rettv->vval.v_list, d);
	    if (wparg != NULL)
		
		return;
	}
    }
}