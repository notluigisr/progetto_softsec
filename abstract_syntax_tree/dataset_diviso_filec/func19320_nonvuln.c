f_stridx(typval_T *argvars, typval_T *rettv)
{
    char_u	buf[NUMBUFLEN];
    char_u	*needle;
    char_u	*haystack;
    char_u	*save_haystack;
    char_u	*pos;
    int		start_idx;

    needle = tv_get_string_chk(&argvars[1]);
    save_haystack = haystack = tv_get_string_buf_chk(&argvars[0], buf);
    rettv->vval.v_number = -1;
    if (needle == NULL || haystack == NULL)
	return;		

    if (argvars[2].v_type != VAR_UNKNOWN)
    {
	int	    error = FALSE;

	start_idx = (int)tv_get_number_chk(&argvars[2], &error);
	if (error || start_idx >= (int)STRLEN(haystack))
	    return;
	if (start_idx >= 0)
	    haystack += start_idx;
    }

    pos	= (char_u *)strstr((char *)haystack, (char *)needle);
    if (pos != NULL)
	rettv->vval.v_number = (varnumber_T)(pos - save_haystack);
}