f_getbufvar(typval_T *argvars, typval_T *rettv)
{
    buf_T	*buf;
    buf_T	*save_curbuf;
    char_u	*varname;
    dictitem_T	*v;
    int		done = FALSE;

    (void)tv_get_number(&argvars[0]);	    
    varname = tv_get_string_chk(&argvars[1]);
    ++emsg_off;
    buf = tv_get_buf(&argvars[0], FALSE);

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    if (buf != NULL && varname != NULL)
    {
	
	save_curbuf = curbuf;
	curbuf = buf;

	if (*varname == '&')
	{
	    if (varname[1] == NUL)
	    {
		
		dict_T	*opts = get_winbuf_options(TRUE);

		if (opts != NULL)
		{
		    rettv_dict_set(rettv, opts);
		    done = TRUE;
		}
	    }
	    else if (get_option_tv(&varname, rettv, TRUE) == OK)
		
		done = TRUE;
	}
	else
	{
	    
	    
	    v = find_var_in_ht(&curbuf->b_vars->dv_hashtab,
							 'b', varname, FALSE);
	    if (v != NULL)
	    {
		copy_tv(&v->di_tv, rettv);
		done = TRUE;
	    }
	}

	
	curbuf = save_curbuf;
    }

    if (!done && argvars[2].v_type != VAR_UNKNOWN)
	
	copy_tv(&argvars[2], rettv);

    --emsg_off;
}