f_setbufvar(typval_T *argvars, typval_T *rettv UNUSED)
{
    buf_T	*buf;
    char_u	*varname, *bufvarname;
    typval_T	*varp;

    if (check_secure())
	return;

    if (in_vim9script()
	    && (check_for_buffer_arg(argvars, 0) == FAIL
		|| check_for_string_arg(argvars, 1) == FAIL))
	return;

    varname = tv_get_string_chk(&argvars[1]);
    buf = tv_get_buf_from_arg(&argvars[0]);
    varp = &argvars[2];

    if (buf != NULL && varname != NULL && varp != NULL)
    {
	if (*varname == '&')
	{
	    aco_save_T	aco;

	    
	    aucmd_prepbuf(&aco, buf);

	    set_option_from_tv(varname + 1, varp);

	    
	    aucmd_restbuf(&aco);
	}
	else
	{
	    bufvarname = alloc(STRLEN(varname) + 3);
	    if (bufvarname != NULL)
	    {
		buf_T *save_curbuf = curbuf;

		curbuf = buf;
		STRCPY(bufvarname, "STR");
		STRCPY(bufvarname + 2, varname);
		set_var(bufvarname, varp, TRUE);
		vim_free(bufvarname);
		curbuf = save_curbuf;
	    }
	}
    }
}