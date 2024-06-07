f_printf(typval_T *argvars, typval_T *rettv)
{
    char_u	buf[NUMBUFLEN];
    int		len;
    char_u	*s;
    int		saved_did_emsg = did_emsg;
    char	*fmt;

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    
    did_emsg = FALSE;
    fmt = (char *)tv_get_string_buf(&argvars[0], buf);
    len = vim_vsnprintf_typval(NULL, 0, fmt, ap, argvars + 1);
    if (!did_emsg)
    {
	s = alloc(len + 1);
	if (s != NULL)
	{
	    rettv->vval.v_string = s;
	    (void)vim_vsnprintf_typval((char *)s, len + 1, fmt,
							      ap, argvars + 1);
	}
    }
    did_emsg |= saved_did_emsg;
}